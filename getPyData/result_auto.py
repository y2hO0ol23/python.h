#lower, upper, casefold

last1 = []
last2 = []
value = []
rng = []
output = ""

cnt = 0;
for i in range(0,0x10FFFF):
    c = chr(i)
    if c.lower() != c:
        if len(c.lower()) == 1:
            val = ord(c.lower()) - i
            if value.count(val) != 1:
                value.append(val)
                last1.append(i)
                last2.append(i - 1)
                rng.append("")
            idx = value.index(val);
            if last2[idx] == i - 1:
                last2[idx] = i
            else:
                if last1[idx] == last2[idx]:
                    rng[idx] += str(last1[idx]) + " "
                elif last1[idx] <= last2[idx]:
                    rng[idx] += str(last1[idx]) + ".." + str(last2[idx]) + " "
                last1[idx] = i
                last2[idx] = i
        else:
            output += "if(_Chr==" + str(i) +"){return \"" + c.lower() + "\";" + "}"

for idx in range(len(rng)):
    if last1[idx] == last2[idx]:
        rng[idx] += str(last1[idx]) + " "
    elif last1[idx] <= last2[idx]:
        rng[idx] += str(last1[idx]) + ".." + str(last2[idx]) + " "


for i in range(len(rng)):
    li = rng[i].split(' ')[:-1]
    output += "if("
    for j in range(len(li)):
        li[j] = li[j].split("..")
        if len(li[j]) == 2:
            output += li[j][0] + "<=_Chr&&_Chr<=" + li[j][1] + "||"
        else:
            output += "_Chr==" + li[j][0] +  "||"
    output += "false){"
    output += "return ord(_Chr)+" + str(value[i]) + ";" + "}"
output += "\nreturn _Chr;" + "\n"

with open("./output.txt","w",encoding="utf-8") as f:
    f.write(output)