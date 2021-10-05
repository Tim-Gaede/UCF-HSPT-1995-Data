program cross;

var infile:text;             (* Text file *)
    p1_word1:string;         (* First word of first pair *)
    p1_word2:string;         (* Second word of first pair *)
    p2_word1:string;         (* First word of second pair *)
    p2_word2:string;         (* Second word of second pair *)
    cross_p1_word1:integer;  (* Position of cross in first word, pair 1 *)
    cross_p1_word2:integer;  (* Position of cross in second word, pair 1 *)
    cross_p2_word1:integer;  (* Position of cross in first word, pair 2 *)
    cross_p2_word2:integer;  (* Position of cross in second word, pair 2 *)



(* Procedure FindCross finds the positions of the leading cross of
 * two words.  If none can be found, -1 is returned in the index variables *)

procedure FindCross(word1, word2:string; var cross_1, cross_2:integer);
var x, y:integer;    (* Looping variables *)
begin
   cross_1:=-1;
   cross_2:=-1;

   (* For each letter in the first word, try to find it in the second word *)
   x:=1;
   while ( (x <= length(word1)) and (cross_1 = -1) ) do
   begin
      y:=1;
      while ( (y <= length(word2)) and (cross_2 = -1) ) do
      begin
         (* If the 2 letters are the same, we have found the leading cross *)
         if word1[x] = word2[y] then
         begin
            cross_1:=x;
            cross_2:=y;
         end;

         y:=y+1;
      end;

      x:=x+1;
   end;
end;


(* Procedure PrintCross produces the output of two pair of crossing words *)

procedure PrintCross(p1_word1, p1_word2, p2_word1, p2_word2:string;
                     p1_cross_1, p1_cross_2, p2_cross_1, p2_cross_2:integer);
var x, y:integer;   (* Looping variables *)
    max_cross_2:integer;   (* Line on which horizontal words will appear *)
    screen:array[1..25, 1..25] of char;   (* An array of the "screen" *)
    num_y_lines:integer;   (* Number of lines to output for this pair *)
begin
   (* Initialize the screen array *)
   for y:=1 to 25 do
   begin
      for x:=1 to 25 do
         screen[y, x]:=' ';
   end;

   (* Find the line that has the horizontal words *)
   if p1_cross_2 > p2_cross_2 then
      max_cross_2:=p1_cross_2
   else
      max_cross_2:=p2_cross_2;

   (* Store the first word of pair 1 into the screen array *)
   for x:=1 to length(p1_word1) do
      screen[max_cross_2, x]:=p1_word1[x];

   (* Store the first word of pair 2 into the screen array *)
   for x:=1 to length(p2_word1) do
      screen[max_cross_2, x+length(p1_word1)+2]:=p2_word1[x];

   (* Store the second word of pair 1 into the screen array *)
   for y:=1 to length(p1_word2) do
      screen[y+max_cross_2-p1_cross_2, p1_cross_1]:=p1_word2[y];

   (* Store the second word of pair 2 into the screen array *)
   for y:=1 to length(p2_word2) do
      screen[y+max_cross_2-p2_cross_2, length(p1_word1)+2+p2_cross_1] :=
         p2_word2[y];

   (* Calculate the number of lines that we need to output *)
   if length(p1_word2)-p1_cross_2 > length(p2_word2)-p2_cross_2 then
      num_y_lines:=max_cross_2 + length(p1_word2) - p1_cross_2
   else
      num_y_lines:=max_cross_2 + length(p2_word2) - p2_cross_2;

   (* Output the answer from our "screen" array *)
   for y:=1 to num_y_lines do
   begin
      for x:=1 to length(p1_word1)+length(p2_word1)+2 do
         write(screen[y][x]);
      writeln;
   end;
end;


begin
   (* Open the input file *)
   assign(infile, 'cross.in');
   reset(infile);

   (* Loop through all cases in the file *)
   while not eof(infile) do
   begin
      (* Read two pair of words *)
      readln(infile, p1_word1);
      readln(infile, p1_word2);
      readln(infile, p2_word1);
      readln(infile, p2_word2);

      (* Find where the first pair crosses if they do *)
      FindCross(p1_word1, p1_word2, cross_p1_word1, cross_p1_word2);

      (* Find where the second pair crosses if they do *)
      FindCross(p2_word1, p2_word2, cross_p2_word1, cross_p2_word2);

      (* If we didn't find a cross in both pairs, output accordingly *)
      if ( (cross_p1_word1 = -1) or (cross_p1_word2 = -1) or
           (cross_p2_word1 = -1) or (cross_p2_word2 = -1) ) then
         writeln('Cannot cross the words.')
      else
         (* Otherwise, output the two crosses *)
         PrintCross(p1_word1, p1_word2, p2_word1, p2_word2, cross_p1_word1,
                    cross_p1_word2, cross_p2_word1, cross_p2_word2);

      (* Put in our blank line between output sets *)
      writeln;
   end;

   (* Close the input file *)
   close(infile);

end.