//
// Copyright (C) 2020 OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef __INET_IEPENERGYSINK_H
#define __INET_IEPENERGYSINK_H

#include "inet/power/contract/IEnergySink.h"

namespace inet {

namespace power {

/**
 * TODO
 *
 * See the corresponding NED file for more details.
 *
 */
class INET_API IEpEnergySink : public virtual IEnergySink
{
  public:
    /**
     * The signal that is used to publish power generation changes.
     */
    static simsignal_t powerGenerationChangedSignal;

  public:
    /**
     * Returns the total power generation in the range [0, +infinity).
     */
    virtual W getTotalPowerGeneration() const = 0;
};

} // namespace power

} // namespace inet

#endif

