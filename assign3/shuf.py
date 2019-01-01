#!/usr/bin/python

import random, sys
from optparse import OptionParser    

class shuf:
    def __init__(self, generator, numlines, tell):
        self.generator = generator
        self.numlines = numlines
        self.tell = tell

    def shuflines(self):
        iterlines = []
        if self.tell:
            for i in range(int(self.generator[0]), int(self.generator[1])+1):
                iterlines.append(i)
            if self.numlines == "default":
                self.numlines = len(iterlines)
        else:
            if self.numlines == "default":
                self.numlines = len(self.generator.lines)
        randlines = [None] * self.numlines
        for i in range(self.numlines):
            if self.tell:
                randlines[i] = random.choice(iterlines)
            else:
                randlines[i] = self.generator.chooseline()
        return randlines

class randline:
    def __init__(self, filename):
        if filename == '-' or filename == "stdin":
            self.lines = sys.stdin.readlines()
        else:
            f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()

    def chooseline(self):
        return random.choice(self.lines)

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--head-count",
                      action="store", dest="numlines", default=None,
                      help="output NUMLINES lines (default all)")
    parser.add_option("-i", "--input-range",
                      action="store", dest="inprange", default="0-0",
                      help="input is the range given (default 0-0)")
    parser.add_option("-r", "--repeat",
                      action="store_true", dest="repeat", default=False,
                      help="output can be repeated (default False)")
    options, args = parser.parse_args(sys.argv[1:])

    try:
        numlines = int(options.numlines)
    except:
        if options.numlines is None:
            numlines = "default"
        else:
            parser.error("invalid NUMLINES: {0}".
                     format(options.numlines))
    inprange = options.inprange
    repeat = bool(options.repeat)
    if numlines is int and numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines))
    if len(args) > 1 and options.repeat == False:
        parser.error("wrong number of operands")

    input_file = 0
    rangenums = 0
    if inprange != "0-0":
        rangenums = inprange.split('-')
    else:
        try:
            input_file = args[0]
        except:
            input_file = "stdin"

    try:
        if rangenums == 0:
            generator = randline(input_file)
        else:
            generator = rangenums
        count = "undec"
        if numlines != "default":
            count = numlines
        while True:
            shuffler = 0
            if inprange != "0-0":
                shuffler = shuf(generator, numlines, True)
            else:
                shuffler = shuf(generator, numlines, False)
            shuffedlines = shuffler.shuflines()
            for line in shuffedlines:
                try:
                    if inprange != "0-0":
                        sys.stdout.write(str(line) + '\n')
                    else:
                        sys.stdout.write(str(line))
                except KeyboardInterrupt:
                    sys.exit()
            if repeat is False:
                break
            if count == numlines and repeat is True:
                break
    except IOError as error:
        errno = error.errno
        strerror = error.strerror
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()
