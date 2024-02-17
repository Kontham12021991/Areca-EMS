# input req the LOCO RANDOM NUM is:7AB9
# input StationtoOnboardRegularPacket.html:153 the STATION RANDOM NUM is:A5A5
# output StationtoOnboardRegularPacket.html:155 the R1 num is:A5A57AB9A5A57AB9
# output StationtoOnboardRegularPacket.html:157 the R2 num is:7AB9A5A57AB9A5A5

# write the function take the two inputs and Provide the R1 and R2 output 


RL = bytes.fromhex("6A52")
RS = bytes.fromhex("9456")


def get_Rnum(LOCOLockRandomNum,StationLockRandomNum):

    R1 = StationLockRandomNum+ LOCOLockRandomNum + StationLockRandomNum + LOCOLockRandomNum
    print(R1)
    R2 = LOCOLockRandomNum + StationLockRandomNum + LOCOLockRandomNum + StationLockRandomNum
    R = R1 + R2
    print(type(R))
    return R  

R2=get_Rnum("7AB9","A5A5")

print("the R2 num is:",R2)

# convert string to list of bytes
def str_to_bytes(s):
    return bytes(s, 'utf-8')

RL = str_to_bytes(R2)
print(type(RL))
# Write te function to convert bytes  to byte array
def bytes_to_bytearray(b):
    return bytearray(b)

RL = bytes_to_bytearray(RL)
print ("The type of RL is ",RL.reverse())
print(type(RL),len(RL))
print(RL)



# # convert hex string to Hex byte array and reverse the array   
# RevHexByteArr = lambda x : bytes.fromhex(x)[::-1]

# # add check sum to the reversed array
# AddCheckSumToArray = lambda x : RevHexByteArr("%02X" % (sum(x) % 256)) + x + RevHexByteArr("%02X" % ((256 - sum(x) % 256) % 256)) 
# AddCheckSumToArray = lambda x : RevHexByteArr(x) + x[0:2] + x[4:6] + x[2:4] + x[6:8]

# checksum = AddCheckSumToArray(bytes.fromhex(str(R2)))
# print('The Check Sum is',checksum)
# print(R2)
# R2 = R2[2:]

# print("s",R2)

# print(RL)
# # R = R1 + R2
# # print(type(R))
# # #write the function to conver string to byte array 
# # def StringToByteArray(s):
# #     return bytearray(s, 'utf-8')

# # B = StringToByteArray(str(R))
# # print("Byte array",B)
# # print(len(B), B)

# # # write the function to reverse the byte array 
# # def Byte_Array_Reverse(B):
# #     B.reverse()
# #     return B
# # B = Byte_Array_Reverse(B)
# # print("Byte_Array_Reverse",B)
# # # write the function to convert string to hex
# # def convert_to_hex(string):
# #     return ''.join([hex(ord(c))[2:] for c in string])
# # print("The type of R is : ",type(R))
# # Hex_R = convert_to_hex(str(R))
# # print("The HEX value of R is : ",Hex_R)
# # # write the functio to reverse
# # def String_Reverse(str):
# #     print(str)
# #     return str[::-1]

