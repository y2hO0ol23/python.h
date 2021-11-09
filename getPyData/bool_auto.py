#isalnum isalpha isAscii isdigit isdecimal isnumeric isprintable isspace
last1 = -1
last2 = -1
rng = ""
output = ""

cnt = 0;
for i in range(0,0x10FFFF):
    c = chr(i)
    if c.isalpha() == True:
        if last2 == -1:
            last1 = i;
            last2 = last2-1;
        if last2 == i - 1:
            last2 = i
        else:
            if last1 == last2:
                rng += str(last1) + " "
            elif last1 <= last2:
                rng += str(last1) + ".." + str(last2) + " "
            last1 = i
            last2 = i
if last1 == last2:
    rng += str(last1) + " "
elif last1 <= last2:
    rng += str(last1) + ".." + str(last2) + " "


li = rng.split(' ')[:-1]
output += "if("
for j in range(len(li)):
    li[j] = li[j].split("..")
    if len(li[j]) == 2:
        output += li[j][0] + "<=_Chr&&_Chr<=" + li[j][1] + "||"
    else:
        output += "_Chr==" + li[j][0] +  "||"
output += "false){"
output += "return true;}" + "\nreturn false;"

with open("./output.txt","w",encoding="utf-8") as f:
    f.write(output)