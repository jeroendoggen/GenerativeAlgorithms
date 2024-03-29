Generative Algorithms
=====================

A simple tool that uses the concept of evolution from biology to solve problems.

I wrote this code while reading the book [The Selfish Gene](http://en.wikipedia.org/wiki/The_Selfish_Gene) by Richard Dawkins.

Program flow:
-------------
 1. Enter a 'secret key'
 2. Generate a random string (parent)
 3. Generate 1000 strings based on the parent (with minor mutations)
 4. Select the child that is closest to the 'secret key' (lowest 'Deltasum')
 5. This child becomes the parent for the next generation
 6. Go back to step 3 until the secret key is found


Example output:
---------------

    $ ./dawkins
    Enter secret key: (followed by enter) (maximum key length:8)
    mysecret
    Secret: m y s e c r e t Checksum secret:876

    Bestdelta: 9999999 Generation: 1 Deltasum: 554 Parent: � � � �   B  
    Bestdelta: 554 Generation: 1 Deltasum: 454 Parent: � � � � v ? B  
    Bestdelta: 454 Generation: 1 Deltasum: 434 Parent: y � � � �  B  
    Bestdelta: 434 Generation: 1 Deltasum: 432 Parent: G � � � T  B : 
    Bestdelta: 432 Generation: 1 Deltasum: 397 Parent: 2 � � � T � B � 
    Bestdelta: 397 Generation: 1 Deltasum: 386 Parent: � @ � � � B : � 
    Bestdelta: 386 Generation: 1 Deltasum: 371 Parent: � r � � T � B
    ....
    1000 failed generations, resetting parent:  n x s e c m f u
    Bestdelta: 10 Generation: 3040 Deltasum: 9 Parent: m w s e c m f u 
    Bestdelta: 9 Generation: 3040 Deltasum: 8 Parent: n x s e c n f u 
    Bestdelta: 8 Generation: 3040 Deltasum: 7 Parent: n y s f c n f t 
    Bestdelta: 7 Generation: 3040 Deltasum: 6 Parent: m x s e c m e t 
    ...
    1000 failed generations, resetting parent:  m y s e c t e u
    Bestdelta: 7 Generation: 13074 Deltasum: 3 Parent: m y s e c t e u 
    Bestdelta: 3 Generation: 13074 Deltasum: 2 Parent: m y s e c t e t 
    Bestdelta: 2 Generation: 13074 Deltasum: 1 Parent: m y s e c s e t 
    Bestdelta: 1 Generation: 13075 Deltasum: 0 Parent: m y s e c r e t
