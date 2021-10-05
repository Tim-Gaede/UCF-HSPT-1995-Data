(***************************************************************************)
(* Tenth Annual UCF ACM/UPE High School Programming Tournament             *)
(* May 3, 1996                                                             *)
(*                                                                         *)
(* Program: PASSWORD                                                       *)
(***************************************************************************)


program password;


var infile:text;   (* Input file *)
    word:string;   (* Input string *)


(* This function checks to see if the string is in all lower-case *)
function allLower(word:string) : boolean;
var ok:boolean;
    i:integer;
begin
   ok:=true;
   for i:=1 to length(word) do
   begin
      (* If a character is not in the range 'a' to 'z', then the string *)
      (* is NOT all lower-case                                          *)
      if not (word[i] in ['a'..'z']) then
         ok:=false;
   end;
   allLower:=ok;
end;


(* This function checks to see if the string is in all upper-case *)
function allUpper(word:string) : boolean;
var ok:boolean;
    i:integer;
begin
   ok:=true;
   for i:=1 to length(word) do
   begin
      (* If a character is not in the range 'A' to 'Z', then the string *)
      (* is NOT all upper-case                                          *)
      if not (word[i] in ['A'..'Z']) then
         ok:=false;
   end;
   allUpper:=ok;
end;


(* This function checks to see if the string is all digits *)
function allDigits(word:string) : boolean;
var ok:boolean;
    i:integer;
begin
   ok:=true;
   for i:=1 to length(word) do
   begin
      (* If a character is not in the range '0' to '9', then the string *)
      (* is NOT all digits                                              *)
      if not (word[i] in ['0'..'9']) then
         ok:=false;
   end;
   allDigits:=ok;
end;


(* This function checks to see if the string is an English word *)
function englishWord(word:string) : boolean;
var ok:boolean;
    onlyLetters:boolean;
    lastConsonant:integer;
    i:integer;
begin
   (* Check and see if the string has only letters *)
   onlyLetters:=true;
   for i:=1 to length(word) do
   begin
      if not (word[i] in ['A'..'Z', 'a'..'z']) then
         onlyLetters:=false;
   end;

   (* If the string has only letters, check to see if every consonant is *)
   (* followed by at least one vowel (a, e, i, o, u) -- except for the   *)
   (* last consonant                                                     *)
   if onlyLetters = true then
   begin
      lastConsonant:=0;
      for i:=1 to length(word) do
      begin
         if (upcase(word[i]) in ['B'..'D', 'F'..'H', 'J'..'N', 'P'..'T', 'V'..'Z']) then
            lastConsonant:=i;
      end;
      ok:=true;

      (* We don't want to check what is after the last letter (whether *)
      (* it's a consonant or a vowel) so don't check it                *)
      for i:=1 to length(word)-1 do
      begin
         (* If the ith letter is a consonant, check for a vowel after *)
         (* it unless it is the last consonant                        *)
         if (i <> lastConsonant) and
            (upcase(word[i]) in ['B'..'D', 'F'..'H', 'J'..'N', 'P'..'T', 'V'..'Z']) then
         begin
            (* If there is not a vowel after the consonant, mark it not ok *)
            if not (upcase(word[i+1]) in ['A', 'E', 'I', 'O', 'U']) then
               ok:=false;
         end;
      end;
   end
   else
      ok:=false;

   (* Return whether the string is an English word or not *)
   englishWord:=ok;
end;

begin
   (* Open the input file *)
   assign(infile, 'password.in');
   reset(infile);

   (* Read until EOF *)
   while not eof(infile) do
   begin
      (* Read the input string and echo it *)
      readln(infile, word);
      writeln(word);

      (* If the string is not all lower-case, not all upper-case, *)
      (* not all digits, not an English word, and is at least 5   *)
      (* characters long, then it's a good password               *)
      if (not allLower(word)) and (not allUpper(word)) and
         (not allDigits(word)) and (not englishWord(word)) and
         (length(word) >= 5) then
         writeln('Good')
      else
         writeln('Not Good');

      (* Don't forget the blank line after the output for each set *)
      writeln;
   end;
end.