import re
import sys
import os


def process(inputFile, out):
    elements = [(line.split(":")[0], line.split(":")[1].strip())
                for line in inputFile if ":" in line and (line.strip())[0] != "#"]
    for type, arguments in elements:
        out.write(type.upper()+" ")
        if type.lower() == "camera":
            pattern = re.compile(
                r"p\((.*)\).*u\((.*)\).*v\((.*)\).*f\((.*)\)")
            m = pattern.match(arguments)
            out.write(" ".join(m.group(1).split(","))+" ")
            out.write(" ".join(m.group(2).split(","))+" ")
            out.write(" ".join(m.group(3).split(","))+" ")
            out.write(m.group(4)+" ")
        elif type.lower() == "sphere":
            pattern = re.compile(r"p\((.*)\).*r\((.*)\)")
            m = pattern.match(arguments)
            out.write(" ".join(m.group(1).split(","))+" ")
            out.write(m.group(2)+" ")
        elif type.lower() == "plane":
            pattern = re.compile(
                r"p\((.*)\).*u\((.*)\).*v\((.*)\).*c\((.*)\)")
            m = pattern.match(arguments)
            out.write(" ".join(m.group(1).split(","))+" ")
            out.write(" ".join(m.group(2).split(","))+" ")
            out.write(" ".join(m.group(3).split(","))+" ")
            out.write(" ".join(m.group(4).split(","))+" ")
        elif type.lower() == "checkeredplane":
            pattern = re.compile(
                r"p\((.*)\).*u\((.*)\).*v\((.*)\).*c1\((.*)\).*c2\((.*?)\).*w\((.*?)\).*h\((.*?)\)")
            m = pattern.match(arguments)
            out.write(" ".join(m.group(1).split(","))+" ")
            out.write(" ".join(m.group(2).split(","))+" ")
            out.write(" ".join(m.group(3).split(","))+" ")
            out.write(" ".join(m.group(4).split(","))+" ")
            out.write(" ".join(m.group(5).split(","))+" ")
            out.write(m.group(6)+" ")
            out.write(m.group(7)+" ")
        elif type.lower() == "checkeredsphere":
            pattern = re.compile(
                r"p\((.*)\).*r\((.*)\).*n\((.*)\).*s\((.*)\).*c1\((.*)\).*c2\((.*?)\)")
            m = pattern.match(arguments)
            out.write(" ".join(m.group(1).split(","))+" ")
            out.write(m.group(2)+" ")
            out.write(" ".join(m.group(3).split(","))+" ")
            out.write(" ".join(m.group(4).split(","))+" ")
            out.write(" ".join(m.group(5).split(","))+" ")
            out.write(" ".join(m.group(6).split(","))+" ")
        elif type.lower() == "triangle":
            pattern = re.compile(
                r"v1\((.*)\).*v2\((.*)\).*v3\((.*)\).*c\((.*)\)")
            m = pattern.match(arguments)
            out.write(" ".join(m.group(1).split(","))+" ")
            out.write(" ".join(m.group(2).split(","))+" ")
            out.write(" ".join(m.group(3).split(","))+" ")
            out.write(" ".join(m.group(4).split(","))+" ")


def main(args):
    if len(args) <= 2:
        print("Usage: python3 scene.py input_file.scene")
    else:
        inputName = sys.argv[1]
        outputName = sys.argv[2]
        f = open(inputName, "r")
        out = open(inputName+".stream", "w")
        process(f, out)
        f.close()
        out.close()
        os.system(
            "./raytracing {} {}".format(inputName+".stream", outputName))


if __name__ == "__main__":
    main(sys.argv)
