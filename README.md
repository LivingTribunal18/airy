# airy

### Syntax Description of our *Language*

<**identifier**> ::= "*a*" | "*b*" | ... | "*z*"

<**literal**> ::= "0" | "1" | ... | "9" 

<**expression**> ::= <**sum**> | <**identifier**> ":" <**literal**>

<**sum**> ::= <**identifier**> "+" <**literal**> | <**identifier**> "+" <**identifier**> | <**literal**> "+" <**literal**>

<**difference**> ::= <**identifier**> "-" <**literal**> | <**identifier**> "-" <**identifier**> | <**literal**> "-" <**literal**>

<**multiplication**> ::= <**identifier**> "*" <**literal**> | <**identifier**> "*" <**identifier**> | <**literal**> "*" <**literal**>

<**divicion**> ::= <**identifier**> "/" <**literal**> | <**identifier**> "/" <**identifier**> | <**literal**> "/" <**literal**>
 
<**initialization**> ::= <**identifier**> ":" <**literal**>
