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

package inet.visualizer.common;

import inet.visualizer.contract.IEnergyStorageVisualizer;

//
// This module integrates canvas and osg energyStorage visualizers into a single module.
//
// @see ~EnergyStorageCanvasVisualizer, ~EnergyStorageOsgVisualizer, ~EnergyStorageVisualizerBase, ~IEnergyStorageVisualizer
//
module EnergyStorageVisualizer like IEnergyStorageVisualizer
{
    parameters:
        @display("i=block/app");
        *.visualizationTargetModule = default("^.^");
        *.visualizationSubjectModule = default("^.^");
    submodules:
        canvasVisualizer: <default(firstAvailableOrEmpty("EnergyStorageCanvasVisualizer"))> like IEnergyStorageVisualizer if typename != "" {
            parameters:
                @display("p=100,100");
        }
        osgVisualizer: <default(firstAvailableOrEmpty("EnergyStorageOsgVisualizer"))> like IEnergyStorageVisualizer if typename != "" {
            parameters:
                @display("p=100,200");
        }
}

