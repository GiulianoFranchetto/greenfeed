#include <UsbComm.h>
#include <base64.h>

UsbComm::UsbComm()
{
    //ctor
}

usb_r UsbComm::ouvrirCommunication(const string phy_ad)
{
    struct termios newtio;

    int fd = open(phy_ad.c_str(), O_RDWR);
    if (fd <0) perror(phy_ad.c_str());

    tcgetattr (fd,&newtio);
    newtio.c_cflag = USB_BAUDRATE | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = ICANON;
    newtio.c_cc[VEOL] = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW, &newtio);
    tcflush(fd, TCIFLUSH);
    this->interface = fd;
    return fd;

}

usb_r UsbComm::envoyerMessage(char* mess, bool changeInB64)
{
    usb_r result=0;
    string encoded;
    if(changeInB64)
        encoded = base64_encode(reinterpret_cast<const unsigned char*>(mess), strlen(mess));
    else
        encoded = mess;
    cout << "Sending " << encoded << endl;
    result = write(this->interface, encoded.c_str(), encoded.size());
    if (encoded.size()>0 && encoded[encoded.size()-1]!='\n') result = write(this->interface, "\n", 1);
    return result;
}

usb_r UsbComm::recevoirMessage(char* mess)
{
    return read (this->interface, mess, BUFF_SIZE);
}

UsbComm::~UsbComm()
{
    close(this->interface);
}
