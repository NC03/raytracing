import re
import sys


def main():
    if len(sys.argv) >= 2:
        with open(sys.argv[1], "r") as f:
            with open(sys.argv[1]+".stream", "w") as out:
                elements = [(line.split(":")[0], line.split(":")[1].strip())
                            for line in f if ":" in line]
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
                            r"p\((.*)\).*u\((.*)\).*v\((.*)\).*c1\((.*)\).*c2\((.*?)\)")
                        m = pattern.match(arguments)
                        out.write(" ".join(m.group(1).split(","))+" ")
                        out.write(" ".join(m.group(2).split(","))+" ")
                        out.write(" ".join(m.group(3).split(","))+" ")
                        out.write(" ".join(m.group(4).split(","))+" ")
                        out.write(" ".join(m.group(5).split(","))+" ")
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
    else:
        print("Usage: python3 scene.py input_file.scene")


if __name__ == "__main__":
    main()
