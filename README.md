# KAI_SA_Cipher

The Caesar Cipher is used to encrypt English messages, and thus, it is easy for a soldier in the Ancient Rome to solve and read the plaintext.

But, if Caesar came to Western Han Dynasty through Silk Road and learned Chinese, he would be able to design a more complicated Cipher skill ( and also get a Chinese name KAI SA ) and confuse the majority of Ancient Rome soldier.

## How to Compile and Run

### Compile
0. you should ensure the compiler's version, I use the compiler gcc 14.2.0 and it works great.
1. typing the command "gcc .\KAI_SA_Cipher.c -o .\KAI_SA_Cipher.exe" (in Windows 10/11)

### Run
1. typing the command ".\KAI_SA_Cipher `Shift` `Option`"
    * `Shift`: the integer that is defined in the type of "C long long" and for more strictly limitation, the Shift should be in range [-2^63 ~ 2^63 - 1]
    * `Option`: 
        - `-d` for decode the string
        - `-e` for encode the string
2. when the code is running, your input(s) is the UTF-8 Chinese String and using '\n' as the signal to make output
3. use `Ctrl+C` or `<88224466AB>` to leave the program

**Tip**: the order of the Chinese word in this program using the pronunciation order, to reduce the effect of near-syllables, you should choose a `Shift` larger than 215 and lower than 18554

## Third Party License

1. 新酷音詞庫: https://github.com/chewing/libchewing-data
``` license
## dc:title,內建字庫,
## dc:rights,Copyright (c) 2025 libchewing Core Team,
## dc:license,LGPL-2.1-or-later,
## dc:identifier,2026.3.20,
```
** modified from libchewing-data:
    - select only the word and its pronunciation columns, without its priority column defined in the original libchewing-data.

2. klib: https://github.com/attractivechaos/klib
``` license
/* The MIT License

   Copyright (c) 2008, 2009, 2011 by Attractive Chaos <attractor@live.co.uk>

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/
```