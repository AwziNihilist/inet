//
// Copyright (C) 2005 OpenSim Ltd.
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

package inet.showcases.wireless.ratecontrol;

import inet.environment.common.PhysicalEnvironment;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.WirelessHost;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.canvas.integrated.IntegratedCanvasVisualizer;


network RateControlShowcase
{
    parameters:
        @display("b=297,203;bgb=1300,460");
    submodules:
        sourceHost: WirelessHost {
            parameters:
                @display("r=,,#707070");
        }
        sinkHost: WirelessHost {
            parameters:
                @display("p=200,200;r=,,#707070");
        }
        physicalEnvironment: PhysicalEnvironment {
            parameters:
                @display("p=131.53847,86.15385");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=130.76924,168.46155");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=131.53847,253.84616");
        }
        visualizer: IntegratedCanvasVisualizer {
            @display("p=131.53847,336.15387");
        }
}

