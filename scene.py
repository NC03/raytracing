import re
import sys
import os

class Object:
    def __init__(self,type,d):
        self.type = type
        self.d = d
    def __str__(self):
        return self.type+": "+str(self.d)
    def isInstance(self,typeName):
        return self.type.lower() == typeName.lower()
    def format(self):
        out = ""
        out += self.type.upper()
        if self.isInstance("camera"):
            out += " "+self.d["p"].replace(","," ")
            out += " "+self.d["u"].replace(","," ")
            out += " "+self.d["v"].replace(","," ")
            out += " "+self.d["f"]
        elif self.isInstance("sphere"):
            out += " "+self.d["p"].replace(","," ")
            out += " "+self.d["r"]
        elif self.isInstance("checkeredsphere"):
            out += " "+self.d["p"].replace(","," ")
            out += " "+self.d["r"]
            out += " "+self.d["n"].replace(","," ")
            out += " "+self.d["s"].replace(","," ")
            out += " "+self.d["c1"].replace(","," ")
            out += " "+self.d["c2"].replace(","," ")
        elif self.isInstance("plane"):
            out += " "+self.d["p"].replace(","," ")
            out += " "+self.d["u"].replace(","," ")
            out += " "+self.d["v"].replace(","," ")
            out += " "+self.d["c"].replace(","," ")
        elif self.isInstance("checkeredplane"):
            out += " "+self.d["p"].replace(","," ")
            out += " "+self.d["u"].replace(","," ")
            out += " "+self.d["v"].replace(","," ")
            out += " "+self.d["c1"].replace(","," ")
            out += " "+self.d["c2"].replace(","," ")
            out += " "+self.d["w"]
            out += " "+self.d["h"]
        elif self.isInstance("triangle"):
            out += " "+self.d["v1"].replace(","," ")
            out += " "+self.d["v2"].replace(","," ")
            out += " "+self.d["v3"].replace(","," ")
            out += " "+self.d["c"].replace(","," ")
        return out

def getArguments(line):
    type, args = line.split(":")
    type = type.strip().lower()
    pattern = re.compile(r"([_\w\d]+)\((.+?)\)")
    return Object(type, dict(pattern.findall(args)))

def process(inputFile, outputFile):
    objects = [getArguments(l) for l in inputFile if ":" in l and l.strip()[0] != "#"]
    for o in objects:
        outputFile.write(o.format()+"\n")

def main(args):
    if len(args) <= 2:
        print("Usage: python3 scene.py input_file.scene output_file.ppm")
    else:
        inputName = sys.argv[1]
        outputName = sys.argv[2]
        f = open(inputName, "r")
        out = open(inputName+".stream", "w")
        process(f, out)
        f.close()
        out.close()
        cmd = "./raytracing {} {}".format(inputName+".stream", outputName)
        os.system(cmd)


if __name__ == "__main__":
    main(sys.argv)
