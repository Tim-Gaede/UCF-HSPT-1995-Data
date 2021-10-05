program salesman;

var infile:text;
    lastHouse:integer;
    houseOfPoliceman:integer;
    i:integer;
    visited:array[2..4999] of boolean;
    caught:boolean;
    numVisited:integer;
    startHouse:integer;
    currentHouse:integer;

begin
   (* Open the input file *)
   assign(infile, 'salesman.in');
   reset(infile);

   (* Process all data sets *)
   while not eof(infile) do
   begin
      readln(infile, lastHouse, houseOfPoliceman);

      (* Initialize visited flags *)
      for i:=2 to lastHouse do
         visited[i]:=false;

      (* Initialize variables *)
      caught:=false;
      numVisited:=0;
      startHouse:=2;

      (* Continue processing visits to houses until salesman is caught *)
      while not caught do
      begin
         (* Go to kth (startHouse-th) house *)
         currentHouse:=startHouse;

         (* Try to visit every kth house *)
         while (not caught) and (currentHouse <= lastHouse) do
         begin
            (* If salesman tries the policeman's house, then he's caught. *)
            (* Otherwise, we count the house as visited, but only if it   *)
            (* hasn't been visited before.                                *)
            if currentHouse = houseOfPoliceman then
               caught:=true
            else if not visited[currentHouse] then
            begin
               visited[currentHouse]:=true;
               inc(numVisited);
            end;

            (* Go to next house *)
            currentHouse:=currentHouse + startHouse;
         end;

         (* Go back to beginning and start with (k+1)th house *)
         inc(startHouse);
      end;

      (* The salesman's been caught so output how many people were visited *)
      writeln('The salesman visits ', numVisited,' people before being caught.');
   end;

   (* Close the input file *)
   close(infile);
end.
