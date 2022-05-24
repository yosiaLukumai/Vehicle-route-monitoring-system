from read_comports_tonet import ReadFromComPorts
COM1 = ReadFromComPorts("COM1", 9600)

# COM1.checkifTheComportisOpen()
COM1.scheduleSendingDataFromPorts('http://localhost:3400/api/backend/routeManager/data', 0.2, 'post', 'xx', ('velocity', 'long', 'lati'))


