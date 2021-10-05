Program Chef;
{
    This solution scans the input line from left to right checking all the
  rules at each character position.  If a rule matches, the replacement
  substring is added to the output string, and the index into the input
  line is incremented by the length of the matching substring (this way,
  we will not match characters that were used to match a previous rule).
  If no rules matched at a character, then that character is added to the
  output string as is.
}

const
      { The table.  Subs[n,1] is replaced by Subs[n,2] }
      Subs : Array[1..29,1..2] of string[5] = ( ('and',   'und'),
                                                ('And',   'Und'),
                                                ('Then',  'Den'),
                                                ('then',  'den'),
                                                ('the',   'der'),
                                                ('The',   'Der'),
                                                ('Yes',   'Ya'),
                                                ('yes',   'ya'),
                                                ('Which', 'Vich'),
                                                ('which', 'vich'),
                                                ('x.',    'xy.'),
                                                ('x ',    'xy '),
                                                ('w ',    'v '),
                                                ('w',     'v'),
                                                ('W',     'V'),
                                                ('d.',    'dy.'),
                                                ('d ',    'dy '),
                                                ('p.',    'py.'),
                                                ('p ',    'py '),
                                                ('v',     'f'),
                                                ('e ',    'ey '),
                                                ('e.',    'ey.'),
                                                ('ir',    'ur'),
                                                ('or',    'ur'),
                                                ('ou',    'oo'),
                                                ('ue',    'oo'),
                                                ('Th',    'D'),
                                                ('th',    'd'),
                                                ('ick',   'ook'));

Var
  InFile         : Text;    { Input file variable                            }
  CurS, InS      : String;  { Output string and search string                }
  Count, SCnt    : Integer; { Line loop variable and Subs loop variable      }
  N, CurPos      : Integer; { Number of lines and substring position         }
  Found          : Boolean; { True if the substring was found at position    }

Begin
  Assign(InFile, 'Chef.in');                 { Open input file }
  reset(InFile);

  Readln(InFile, N);                         { Read in the number of lines }
  For Count := 1 to N Do
    Begin
      Readln(InFile,InS);
      CurS := '';

      CurPos := 1;                           { Search line from left to right }
      While CurPos <= Length(InS) Do
        Begin
          Found := False;
          For SCnt := 1 to 29 Do             { Check each rule at current position }
            if (not found) and (SubS[SCnt,1] = Copy(InS, CurPos, Length(SubS[SCnt,1]))) then
              Begin
                Found := True;
                CurS := CurS + SubS[SCnt,2];
                CurPos := CurPos + Length(SubS[SCnt,1]);
              End;

          If not Found Then                  { If no match, then add character as is }
            Begin
              CurS := CurS + InS[CurPos];
              CurPos := CurPos + 1;
            End;
        End;

      Writeln(CurS);                         { Output the finished string }
    End;


  Close(InFile);
End.
