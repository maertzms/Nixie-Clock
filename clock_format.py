# data type used for nixie clock time to gpio translation
class TimeNum:
    # class object variables
    # Digit Values
    b0_d = 0
    b1_c = 0
    b2_b = 0
    b3_a = 0

    # Bit locations
    bL = [2, 2, 2, 2]

    def __init__(self, msb_d:int = 0, 2msb_c:int = 0, 2lsb_b:int = 0, lsb_a:int = 0): # -> specifies return type
        self.b0_d = msb_d
        self.b1_c = 2msb_c
        self.b2_b = 2lsb_b
        self.b3_a = lsb_a

    def setBits(self, num_in:int):
        temp = '{0:04b}'.format(num_in)
        self.b0_d:int = temp[0]
        self.b1_c:int = temp[1]
        self.b2_b:int = temp[2]
        self.b3_a:int = temp[3]

    def setLocations(self, b0 = 2, b1 = 2, b2 = 2, b3 = 2):
        self.bL = [b0, b1, b2, b3]

    def writeDigit(self):
        
