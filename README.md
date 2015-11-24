# yasa

## Description

yasa is a program that aligns two translations of a text sentence by sentence in order to produce a bi-text.

It handles many file formats and supports personal lexicons.  It also uses highly configurable dynamic programming algorithms to find the optimal alignment.
 
Although good sentence aligners are freely available, our laboratory regularly receives requests from researchers and industries for aligning parallel data. This motivated us to release yet another open-source sentence aligner we wrote nearly 20 years ago. This aligner is simple but it performs surprisingly well and often better than more elaborated ones, and do so very fast, allowing to align very large corpora.

Originally created by [Philippe Langlais](http://www.iro.umontreal.ca/~felipe/), it was reimplemented by [Alexandre Patry](https://www.linkedin.com/in/patry). It was reborn as yasa as part of improvements made during Fethi Lamraoui's masters thesis. [An article describing the new algorithm](http://rali.iro.umontreal.ca/rali/?q=node/1336) is available on our website. Should you use our tool in your research, we would appreciate a citation to this article.

To build and install it, follow the procedure explained in the INSTALL file. Make sure
you have the Boost libraries installed prior to compiling.

When you use Yasa in your research, we would appreciate that you include
a citation to the relevant article:

    @conference {yasa2013,
        title = {Yet Another Fast, Robust and Open Source Sentence Aligner. Time to Reconsider Sentence Alignment?},
        booktitle = {XIV Machine Translation Summit},
        year = {2013},
        month = {Sept.},
        address = {Nice, France},
        author = {Lamraoui, Fethi and Langlais, Philippe}
    }


## Usage

The program expects documents encoded in UTF-8. As such, it will start by
setting its locale to en_US.UTF-8. If the locale is not found on the system,
it will revert to the system's locale. In the latter case, it is up to the user
to make sure this locale specifies a UTF-8 encoding. Other encodings will produced
flawed results.

To get help, read the man page or run

    yasa -h

Here are a few examples of YASA's invocation.

    yasa -i o -o o source.ospl target.ospl result.alignment
    
will align two texts that are tokenized in the one sentence per line format and
output a result (result.alignment) showing the sentence alignment. The format
is simple and looks like this:

    1-1 1.53842
    2-1 2.90837
    1-2 4.77317
    1-1 6.16061
    1-1 6.16061
    1-1 6.72474
    ...
       
It shows the alignment pairs (1-1: 1 source line aligned with 1 target line;
2-1: 2 source lines aligned with 1 target line, etc.) as well as the cumulative
score for the alignment. More in our article. 

Other examples:


    yasa -i c -o r source.ces target.ces result

will align two texts that are tokenized in the cesAna format and will output
the alignment in a user friendly format.

    yasa -i o -e c -b 20 -o c source.ospl target.ospl

will align two texts that are tokenized in the One Sentence Per Line format.

## More information

More info [on our website](http://rali.iro.umontreal.ca/rali/?q=en/yasa).

Contact: Philippe Langlais, [felipe@iro.umontreal.ca](mailto:felipe@iro.umontreal.ca)
