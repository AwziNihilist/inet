//
// (C) 2013 Opensim Ltd.
//
// This library is free software, you can redistribute it
// and/or modify
// it under  the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// Author: Andras Varga (andras@omnetpp.org)
//

#include "inet/common/IInterfaceRegistrationListener.h"
#include "inet/common/ModuleAccess.h"
#include "inet/linklayer/base/MacProtocolBase.h"

namespace inet {

MacProtocolBase::MacProtocolBase()
{
}

MacProtocolBase::~MacProtocolBase()
{
    delete currentTxFrame;
}

MacAddress MacProtocolBase::parseMacAddressParameter(const char *addrstr)
{
    MacAddress address;

    if (!strcmp(addrstr, "auto"))
        // assign automatic address
        address = MacAddress::generateAutoAddress();
    else
        address.setAddress(addrstr);

    return address;
}

void MacProtocolBase::initialize(int stage)
{
    LayeredProtocolBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        upperLayerInGateId = findGate("upperLayerIn");
        upperLayerOutGateId = findGate("upperLayerOut");
        lowerLayerInGateId = findGate("lowerLayerIn");
        lowerLayerOutGateId = findGate("lowerLayerOut");
    }
    else if (stage == INITSTAGE_NETWORK_INTERFACE_CONFIGURATION)
        registerInterface();
}

void MacProtocolBase::registerInterface()
{
    ASSERT(interfaceEntry == nullptr);
    interfaceEntry = getContainingNicModule(this);
    configureInterfaceEntry();
}

void MacProtocolBase::sendUp(cMessage *message)
{
    if (message->isPacket())
        emit(packetSentToUpperSignal, message);
    send(message, upperLayerOutGateId);
}

void MacProtocolBase::sendDown(cMessage *message)
{
    if (message->isPacket())
        emit(packetSentToLowerSignal, message);
    send(message, lowerLayerOutGateId);
}

bool MacProtocolBase::isUpperMessage(cMessage *message)
{
    return message->getArrivalGateId() == upperLayerInGateId;
}

bool MacProtocolBase::isLowerMessage(cMessage *message)
{
    return message->getArrivalGateId() == lowerLayerInGateId;
}

void MacProtocolBase::deleteCurrentTxFrame()
{
    delete currentTxFrame;
    currentTxFrame = nullptr;
}

void MacProtocolBase::dropCurrentTxFrame(PacketDropDetails& details)
{
    emit(packetDroppedSignal, currentTxFrame, &details);
    delete currentTxFrame;
    currentTxFrame = nullptr;
}

void MacProtocolBase::popFromTransmissionQueue()
{
    if (currentTxFrame != nullptr)
        throw cRuntimeError("Model error: incomplete transmission exists");
    ASSERT(transmissionQueue != nullptr);
    currentTxFrame = transmissionQueue->popPacket();
}

void MacProtocolBase::flushQueue(PacketDropDetails& details)
{
    // code would look slightly nicer with a pop() function that returns nullptr if empty
    if (transmissionQueue)
        while (!transmissionQueue->isEmpty()) {
            auto packet = transmissionQueue->popPacket();
            emit(packetDroppedSignal, packet, &details); //FIXME this signal lumps together packets from the network and packets from higher layers! separate them
            delete packet;
        }
}

void MacProtocolBase::clearQueue()
{
    if (transmissionQueue)
        while (!transmissionQueue->isEmpty())
            delete transmissionQueue->popPacket();
}

} // namespace inet

