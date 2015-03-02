/* 
 * File:   CiCreateDef.cpp
 * Author: martin
 * 
 * Created on Sobota, 2013, február 23, 13:47
 */

#include "CiCreateDef.h"

CiCreateDef::CiCreateDef() : CComport() {
}

CiCreateDef::CiCreateDef(const char *cp, int bd) : CComport(cp, bd) {
}

int CiCreateDef::ConnectToPort() {
    return OpenComport();
}

int CiCreateDef::SendToCreate(unsigned char OI_code) {
    //SendByte(COMMAND_CREATE);
    return SendByte(OI_code);
}

int CiCreateDef::SendToCreate(unsigned char OI_code, unsigned char data1) {
    unsigned char data[2];

    data[0] = OI_code;
    data[1] = data1;
    //SendByte(COMMAND_CREATE);
    return SendnBytes(&(data[0]), 2);
}

int CiCreateDef::SendToCreate(unsigned char OI_code, WORD data1) {
    unsigned char data[3];

    union pomoc_t {
        short int data;
        unsigned char datab[2];
    } pomoc1;

    data[0] = OI_code;
    pomoc1.data = data1;
    //treba poslať odzadu
    data[1] = pomoc1.datab[1];
    data[2] = pomoc1.datab[0];

    //SendByte(COMMAND_CREATE);
    return SendnBytes(&(data[0]), 3);

}

int CiCreateDef::SendToCreate(unsigned char OI_code, WORD data1, WORD data2) {
    unsigned char data[5];

    union pomoc_t {
        short int data;
        unsigned char datab[2];
    } pomoc1;

    data[0] = OI_code;
    pomoc1.data = data1;
    //treba poslať odzadu
    data[1] = pomoc1.datab[1];
    data[2] = pomoc1.datab[0];
    pomoc1.data = data2;
    //treba poslať odzadu
    data[3] = pomoc1.datab[1];
    data[4] = pomoc1.datab[0];

    //SendByte(COMMAND_CREATE);
    return SendnBytes(&(data[0]), 5);
}

int CiCreateDef::SendToCreate(unsigned char OI_code, int NumOfBytes, unsigned char *data) {
    int pocet;

    //SendByte(COMMAND_CREATE);
    pocet = SendByte(OI_code);
    pocet += SendBuf(data, NumOfBytes);
    return pocet;
}

int CiCreateDef::ReceivePacketFromCreate(CreateSensors &IO_SENSORS_CREATE, unsigned char packet) {
    unsigned char *dataR;
    DWORD pocet;
    dataR = (unsigned char*) malloc(100);
    pocet = PollComport(dataR, 100);
    
    //std::cout << "ma byt" << OI_PacketSize[packet]+COMMAND_CREATE_SYZE << " prislo" << pocet << "\n";
    /*union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *(dataR + 13);
    pomoc1.datab[0] = *(dataR + 14);
    std::cout << "zmena polohy" << pomoc1.data << "\n";*/
    
    
    if (pocet == OI_PacketSize[packet]) {
        //std::cout << "prvy" << static_cast<int>(*(dataR)) << "\n";
        DecodeSensorsFromPacket(IO_SENSORS_CREATE, packet, dataR);
        return pocet;
    } else {
        std::cout << "došiel chybný packet\n";
    }
    return -1;
}

int CiCreateDef::DecodeSensorsFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char packet, unsigned char *data) {
    int i = 0;
    int index = 0;
    for (i = OI_PacketID[packet][0]; i <= OI_PacketID[packet][1]; i++) {
        switch (i) {
            case 7:
                DecodeBumsAndWheelsFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 8:
                DecodeWallFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 9:
                DecodeCliffLeftFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 10:
                DecodeCliffFrontLeftFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 11:
                DecodeCliffFrontRightFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 12:
                DecodeCliffRightFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 13:
                DecodeVirtualWallFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 14:
                DecodeLSDandWheelOvercurrentFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 15:
                index++;
                break;
            case 16:
                index++;
                break;
            case 17:
                DecodeIRFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 18:
                DecodeButtonsFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 19:
                DecodeDistanceFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 20:DecodeAngleFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 21:
                DecodeChargingStateFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 22:
                DecodeVoltageFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 23:
                DecodeCurrentFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 24:
                DecodeBatteryTemperatureFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 25:
                DecodeBatteryChargeFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 26:
                DecodeBatteryCapacityFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 27:
                DecodeWallSignalFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 28:
                DecodeCliffLeftSignalFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 29:
                DecodeCliffFrontLeftSignalFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 30:
                DecodeCliffFrontRightSignalFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 31:
                DecodeCliffRightSignalFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 32:
                DecodeCargobayDigitalInputFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 33:
                DecodeCargobayAnalogSignalFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 34:
                DecodeChargingSourceAvailableFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 35:
                DecodeOImodeFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 36:
                DecodeSongNumberFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 37:
                DecodeSongPlayingFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 38:
                DecodeNumberOfStreamPacketsFromPacket(IO_SENSORS_CREATE, *(data + index));
                index++;
                break;
            case 39:
                DecodeRequestedVelocityFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 40:
                DecodeRequestedRadiusFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 41:
                DecodeRequestedRightVelocityFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            case 42:
                DecodeRequestedLeftVelocityFromPacket(IO_SENSORS_CREATE, (data + index));
                index += 2;
                break;
            default:
                break;
        }
    }
    return 0;
}

void CiCreateDef::DecodeBumsAndWheelsFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data) //id7
{
    IO_SENSORS_CREATE.BumpRight = data & 0x01; // bitove and, iba ak je bit z najnizsou vahou rovny 1 bude vysledok rovny 1
    IO_SENSORS_CREATE.BumpLeft = (data & 0x02) / 2;
    IO_SENSORS_CREATE.WheelpdropRight = (data & 0x04) / 4;
    IO_SENSORS_CREATE.WheelpdropLeft = (data & 0x08) / 8;
    IO_SENSORS_CREATE.WheelpdropCaster = (data & 0x10) / 16;
}

void CiCreateDef::DecodeWallFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data) //id8
{
    IO_SENSORS_CREATE.Wall = data;
}

void CiCreateDef::DecodeCliffLeftFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data) //id9
{
    IO_SENSORS_CREATE.CliffLeft = data;
}

void CiCreateDef::DecodeCliffFrontLeftFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id10
{
    IO_SENSORS_CREATE.CliffFrontLeft = data;
}

void CiCreateDef::DecodeCliffFrontRightFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id11
{
    IO_SENSORS_CREATE.CliffFrontRight = data;
}

void CiCreateDef::DecodeCliffRightFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id12
{
    IO_SENSORS_CREATE.CliffRight = data;
}

void CiCreateDef::DecodeVirtualWallFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id13
{
    IO_SENSORS_CREATE.VirtualWall = data;
}

void CiCreateDef::DecodeLSDandWheelOvercurrentFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id14
{
    IO_SENSORS_CREATE.LSD1overcurrent = data & 0x01; // bitove and, iba ak je bit z najnizsou vahou rovny 1 bude vysledok rovny 1
    IO_SENSORS_CREATE.LSD0overcurrent = (data & 0x02) / 2;
    IO_SENSORS_CREATE.LSD2overcurrent = (data & 0x04) / 4;
    IO_SENSORS_CREATE.RightWheelovercurrent = (data & 0x08) / 8;
    IO_SENSORS_CREATE.LeftWheelovercurrent = (data & 0x10) / 16;
}

void CiCreateDef::DecodeIRFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id17
{
    IO_SENSORS_CREATE.IRbyte = data;

}

void CiCreateDef::DecodeButtonsFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id18
{
    IO_SENSORS_CREATE.PlayPressed = data & 0x01; // bitove and, iba ak je bit z najnizsou vahou rovny 1 bude vysledok rovny 1
    IO_SENSORS_CREATE.AdvancePressed = (data & 0x04) / 4;

}

void CiCreateDef::DecodeDistanceFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id19
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.Distance = pomoc1.data;

    //std::cout << "zmena polohy" << pomoc1.data << "\n";

}

void CiCreateDef::DecodeAngleFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id20
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.Angle = pomoc1.data;

    //std::cout << "zmena uhlu" << pomoc1.data << "\n";

}

void CiCreateDef::DecodeChargingStateFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id21
{
    IO_SENSORS_CREATE.ChargingState = data;
}

void CiCreateDef::DecodeVoltageFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id 22
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.Voltage = pomoc1.data;


}

void CiCreateDef::DecodeCurrentFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id 23
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.Current = pomoc1.data;


}

void CiCreateDef::DecodeBatteryTemperatureFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id24
{
    IO_SENSORS_CREATE.BatteryTemperature = (char) data;

}

void CiCreateDef::DecodeBatteryChargeFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id25
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.BatteryCharge = pomoc1.data;


}

void CiCreateDef::DecodeBatteryCapacityFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id26
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.BatteryCapacity = pomoc1.data;


}

void CiCreateDef::DecodeWallSignalFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id27
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.WallSignal = pomoc1.data;


}

void CiCreateDef::DecodeCliffLeftSignalFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id28
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.CliffLeftSignal = pomoc1.data;


}

void CiCreateDef::DecodeCliffFrontLeftSignalFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id29
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.CliffFrontLeftSignal = pomoc1.data;


}

void CiCreateDef::DecodeCliffFrontRightSignalFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id30
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.CliffFrontRightSignal = pomoc1.data;


}

void CiCreateDef::DecodeCliffRightSignalFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id31
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.CliffRightSignal = pomoc1.data;


}

void CiCreateDef::DecodeCargobayDigitalInputFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id32
{
    IO_SENSORS_CREATE.CargoBayDigitalInput0 = data & 0x01; // bitove and, iba ak je bit z najnizsou vahou rovny 1 bude vysledok rovny 1
    IO_SENSORS_CREATE.CargoBayDigitalInput1 = (data & 0x02) / 2;
    IO_SENSORS_CREATE.CargoBayDigitalInput2 = (data & 0x04) / 4;
    IO_SENSORS_CREATE.CargoBayDigitalInput3 = (data & 0x08) / 8;
    IO_SENSORS_CREATE.DeviceDetect_BaudRateChange = (data & 0x10) / 16;
}

void CiCreateDef::DecodeCargobayAnalogSignalFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id33
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.CargoBayAnalogSignal = pomoc1.data;


}

void CiCreateDef::DecodeChargingSourceAvailableFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id34
{
    IO_SENSORS_CREATE.InternalCharger = data & 0x01; // bitove and, iba ak je bit z najnizsou vahou rovny 1 bude vysledok rovny 1
    IO_SENSORS_CREATE.HomaBaseCharger = (data & 0x02) / 2;

}

void CiCreateDef::DecodeOImodeFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id35
{
    IO_SENSORS_CREATE.OImode = data;

}

void CiCreateDef::DecodeSongNumberFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id36
{
    IO_SENSORS_CREATE.SongNumber = data;

}

void CiCreateDef::DecodeSongPlayingFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id37
{
    IO_SENSORS_CREATE.SongPlaying = data;

}

void CiCreateDef::DecodeNumberOfStreamPacketsFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char data)//id38
{
    IO_SENSORS_CREATE.NumberOfStreamPAckets = data;

}

void CiCreateDef::DecodeRequestedVelocityFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id39
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[0] = *data;
    pomoc1.datab[1] = *(data + 1);
    IO_SENSORS_CREATE.RequestedVelocity = pomoc1.data;


}

void CiCreateDef::DecodeRequestedRadiusFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id40
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[0] = *data;
    pomoc1.datab[1] = *(data + 1);
    IO_SENSORS_CREATE.RequestedRadius = pomoc1.data;


}

void CiCreateDef::DecodeRequestedRightVelocityFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id41
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.RequestedRightVelocity = pomoc1.data;


}

void CiCreateDef::DecodeRequestedLeftVelocityFromPacket(CreateSensors &IO_SENSORS_CREATE, unsigned char *data)//id42
{

    union pomoc_t {
        WORD data;
        unsigned char datab[2];
    } pomoc1;
    pomoc1.datab[1] = *data;
    pomoc1.datab[0] = *(data + 1);
    IO_SENSORS_CREATE.RequestedLeftVelocity = pomoc1.data;


}

void CiCreateDef::UpdateSensorsStates() {
    //vyžiada packet so všetkými informáciami
    SendToCreate(OI_SENSORS, (unsigned char) 6);
    ReceivePacketFromCreate(sensors, (unsigned char) 6);
}

void CiCreateDef::UpdateSomeSensorsStates() {
    //vyžiada packet so všetkými informáciami
    
    // distance
    SendToCreate(OI_SENSORS, (unsigned char) 19);
    ReceivePacketFromCreate(sensors, (unsigned char) 19);
    usleep(10*1000);
    
    //angle
    SendToCreate(OI_SENSORS, (unsigned char) 20);
    ReceivePacketFromCreate(sensors, (unsigned char) 20);
    usleep(10*1000);
    
    //Bumps and Wheel Drops
    SendToCreate(OI_SENSORS, (unsigned char) 7);
    ReceivePacketFromCreate(sensors, (unsigned char) 7);
    usleep(10*1000);
    
    //wall
    SendToCreate(OI_SENSORS, (unsigned char) 8);
    ReceivePacketFromCreate(sensors, (unsigned char) 8);
    usleep(10*1000);
    
    //wall signal
    SendToCreate(OI_SENSORS, (unsigned char) 21);
    ReceivePacketFromCreate(sensors, (unsigned char) 21);
    usleep(10*1000);
}

int CiCreateDef::getLastDistance() {
    if ((sensors.Distance < 50) && (sensors.Distance > -50)) {
        return sensors.Distance;
    } else {
        return 0;
    }
}

int CiCreateDef::getLastAngle() {
    if ((sensors.Angle < 30) && (sensors.Angle > -30)) {
        return sensors.Angle;
    } else {
        return 0;
    }
}

int CiCreateDef::getBumpLeft() {
    return sensors.BumpLeft;
}

int CiCreateDef::getBumpRight() {
    return sensors.BumpRight;
}

int CiCreateDef::getWall() {
    return sensors.Wall;
}

int CiCreateDef::getWallSingal() {
    return sensors.WallSignal;
}

int CiCreateDef::getBatteryNapatie() {
    if (sensors.BatteryCapacity == 0) return 0;
    return (int) ((float)sensors.BatteryCharge / (float)sensors.BatteryCapacity * 100);
}

char CiCreateDef::getBatteryTeplota() {
    return sensors.BatteryTemperature;
}

int CiCreateDef::getZdvihnutie() {
    return (sensors.WheelpdropLeft || sensors.WheelpdropRight);
}

int CiCreateDef::getSchody() {
    return (sensors.CliffFrontLeft || sensors.CliffFrontRight || sensors.CliffLeft || sensors.CliffRight);
}

CiCreateDef::~CiCreateDef() {
    // destruktor ccomport sa vola automaticky po tomto
    std::cout << "destruktor CiCreateDef\n";
}

