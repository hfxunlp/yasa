# yasa

## Description

yasa is a program that aligns two translations of a text sentence by sentence in order to produce a bi-text.

It handles many file formats and supports personal lexicons.  It also uses highly configurable dynamic programming algorithms to find the optimal alignment.
 
Although good sentence aligners are freely available, our laboratory regularly receives requests from researchers and industries for aligning parallel data. This motivated us to release yet another open-source sentence aligner we wrote nearly 20 years ago. This aligner is simple but it performs surprisingly well and often better than more elaborated ones, and do so very fast, allowing to align very large corpora.

Originally created by [Philippe Langlais](http://www.iro.umontreal.ca/~felipe/), it was reimplemented by [Alexandre Patry](https://www.linkedin.com/in/patry). It was reborn as yasa as part of improvements made during Fethi Lamraoui's masters thesis. [An article describing the new algorithm](http://rali.iro.umontreal.ca/rali/?q=node/1336) is available on our website. Should you use our tool in your research, we would appreciate a citation to this article.

To build and install it, follow the procedure explained in the INSTALL file.

## Usage

Because the man page does a good job at describing the program's usage, 
details are not explained here, but to whet your appetite, here is
an example of YASA's invocation.

    yasa -i c -o f source.ces target.ces result

will align two texts that are tokenized in the cesAna format and will output
the alignment in a user friendly format.

    yasa -i o -e c -b 20 -o c source.ospl target.ospl

will align two texts that are tokenized in the One Sentence Per Line format.

## More information

More info [on our website](http://rali.iro.umontreal.ca/rali/?q=en/yasa).

Read also the README file in this directory.

Contact: Philippe Langlais, [felipe@iro.umontreal.ca](mailto:felipe@iro.umontreal.ca)
