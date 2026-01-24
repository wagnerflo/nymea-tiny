// SPDX-License-Identifier: LGPL-3.0-or-later

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Copyright (C) 2013 - 2024, nymea GmbH
* Copyright (C) 2024 - 2025, chargebyte austria GmbH
*
* This file is part of nymea.
*
* nymea is free software: you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* as published by the Free Software Foundation, either version 3
* of the License, or (at your option) any later version.
*
* nymea is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with nymea. If not, see <https://www.gnu.org/licenses/>.
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef HARDWAREMANAGERIMPLEMENTATION_H
#define HARDWAREMANAGERIMPLEMENTATION_H

#include <QObject>
#include <QNetworkAccessManager>

#include "hardwaremanager.h"

namespace nymeaserver {

class Platform;
class MqttBroker;
class ZigbeeManager;
class ZigbeeHardwareResourceImplementation;
class ZWaveManager;
class ZWaveHardwareResourceImplementation;
class ModbusRtuManager;
class ModbusRtuHardwareResourceImplementation;
class NetworkDeviceDiscoveryImpl;

class HardwareManagerImplementation : public HardwareManager
{
    Q_OBJECT

public:
    explicit HardwareManagerImplementation(Platform *platform, MqttBroker *mqttBroker, ZigbeeManager *zigbeeManager, ZWaveManager *zwaveManager, ModbusRtuManager *modbusRtuManager, QObject *parent = nullptr);
    ~HardwareManagerImplementation() override;

#ifdef WITH_RT433
    Radio433 *radio433() override;
#endif
    PluginTimerManager *pluginTimerManager() override;
    NetworkAccessManager *networkManager() override;
    UpnpDiscovery *upnpDiscovery() override;
    PlatformZeroConfController *zeroConfController() override;
#ifdef WITH_BT
    BluetoothLowEnergyManager *bluetoothLowEnergyManager() override;
#endif
    MqttProvider *mqttProvider() override;
    I2CManager *i2cManager() override;
    ZigbeeHardwareResource *zigbeeResource() override;
    ZWaveHardwareResource *zwaveResource() override;
#ifdef WITH_MODBUS
    ModbusRtuHardwareResource *modbusRtuResource() override;
#endif
    NetworkDeviceDiscovery *networkDeviceDiscovery() override;

public slots:
    void thingsLoaded();

private:
    QNetworkAccessManager *m_networkAccessManager = nullptr;

    Platform *m_platform = nullptr;

    // Hardware Resources
    PluginTimerManager *m_pluginTimerManager = nullptr;
#ifdef WITH_RT433
    Radio433 *m_radio433 = nullptr;
#endif
    NetworkAccessManager *m_networkManager = nullptr;
    UpnpDiscovery *m_upnpDiscovery = nullptr;
#ifdef WITH_BT
    BluetoothLowEnergyManager *m_bluetoothLowEnergyManager = nullptr;
#endif
    MqttProvider *m_mqttProvider = nullptr;
    I2CManager *m_i2cManager = nullptr;
    ZigbeeHardwareResourceImplementation *m_zigbeeResource = nullptr;
    ZWaveHardwareResourceImplementation *m_zwaveResource = nullptr;
#ifdef WITH_MODBUS
    ModbusRtuHardwareResourceImplementation *m_modbusRtuResource = nullptr;
#endif
    NetworkDeviceDiscoveryImpl *m_networkDeviceDiscovery = nullptr;

};

}

#endif // HARDWAREMANAGERIMPLEMENTATION_H
