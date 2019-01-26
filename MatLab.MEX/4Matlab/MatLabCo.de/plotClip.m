function [AminusB,AminusBIdx,AminusBn,AminusBarea, ...
 					BminusA,BminusAIdx,BminusAn,BminusAarea, ...
 					AandB,AandBIdx,AandBn,AandBarea]=plotClip(polyA,polyB)
% plotClip - Take two polygons, clip them against each other, and 
%            then plot the three clipped regions---A - B, 
%            B - A, A and B---in turn. Also calculate the area 
%            for A - B, B - A, and A & B.
%
%Call: [AminusB,AminusBIdx,AminusBn,AminusBarea, ...
%				BminusA,BminusAIdx,BminusAn,BminusAarea, ...
%				AandB,AandBIdx,AandBn,AandBarea]=plotClip(polyA,polyB)
%
%Input:
%	polyX - 2 x N matrix of (x,y) vertices. x in first row, y in second row.
%         Last vertex does not have to equal first vertex for closure to
%         occur.
%
%Output: Plot of a clipped polygon pair.
% AminusB     - a 2 x N sequential list of polygon vertices; N is the 
%               total count of all vertices for all polygons passed out 
%               for the set A - B
% AminusBIdx  - 1 x AminusBn vector where each element contains the 
%               number of vertices for each polygon in the set A - B; 
%               the sum of all these elements equals N
% AminusBn    - scalar containing the number of polygons for the set 
%               A - B
%AminusBarea - 1 x AminusBn vector where each element contains the area
%              for each polygon in the set A - B; the sign indicates 
%              clockwise (negative) or counter-clockwise (positive)              
%
%BminusA     - a 2 x N sequential list of polygon vertices; N is the 
%              total count of all vertices for all polygons passed out 
%              for the set B - A
%BminusAIdx  - 1 x BminusAn vector where each element contains the 
%              number of vertices for each polygon in the set B - A; 
%              the sum of all these elements equals N
%BminusAn    - scalar containing the number of polygons for the set 
%              B - A
%BminusAarea - 1 x BminusAn vector where each element contains the area
%              for each polygon in the set B - A; the sign indicates 
%              clockwise (negative) or counter-clockwise (positive)
%              
%AandB       - a 2 x N sequential list of polygon vertices; N is the 
%              total count of all vertices for all polygons passed out 
%              for the set A & B
%AandBIdx    - 1 x AandBn vector where each element contains the number 
%              of vertices for each polygon in the set A & B; the sum of 
%              all these elements equals N
%AandBn      - scalar containing the number of polygons for the set A & B
%AandBarea   - 1 x AandBn vector where each element contains the area
%              for each polygon in the set A & B; the sign indicates 
%              clockwise (negative) or counter-clockwise (positive)
%
%Notes:
% If the polygons polyA and polyB are not loaded in the workspace, use
% a default pair that forms the Star of David.
% I have included other polygon pairs that you can load with the command
% load FILENAME
% where FILENAME is one of case1, case2, case3 or in_file. You can also
% use the Load Workspace... command in the file menu to accomplish the
% same thing. gsl
%
%Gregg Leichtman, 10/30/96
%Version 1.2
%
%Modifications:
% Converted from a script to a function. gsl 1/14/97
%
% Added code to transpose input polygons from N x 2 to 2 x N
% if necessary. gsl 1/17/97
%
% Changed A & B polygon output color from white to blue. - gsl 1/23/97
%
% Added "lt = setstr(lt);" after setting each line type. Matlab 5.x
% needed explicit statement to force matrix into a string type.
% gsl 5/12/97
%


%'Loading input polygons...'
if ~ exist('polyA')
polyA = [1     0     2     1; ...
        -1     1     1    -1]
end
if ~ exist('polyB')
polyB = [0     1     2     0; ...
         0     2     0     0]
end
% Could also use:
%polyA = [1     0     2; ...
%        -1     1     1]
%polyB = [0     1     2; ...
%         0     2     0]

%disp('Plotting...')

% Clear figure.
clf

% Make sure vertex matrices are oriented as 2 x N.
s = size(polyA);
if s(1) > 2
	polyA = polyA';
end
s = size(polyB);
if s(1) > 2
	polyB = polyB';
end

% Input polygons: A, B
subplot(2,2,1)
pltPolys([polyA polyB],[max(size(polyA)) max(size(polyB))],2,['r-'; 'g-'])
title('Input Polygons A (Red) and B (Green)')

% Clip the polygon pair.
%disp('Clipping polygons...')
[AminusB,AminusBIdx,AminusBn,AminusBarea, ...
 BminusA,BminusAIdx,BminusAn,BminusAarea, ...
 AandB,AandBIdx,AandBn,AandBarea]=clippoly(polyA,polyB);

% The sign of the area indicates the clockwise-negative sign-or counter-clockwise-positive
% sign-ordering of the polygon vertices. For this application, output only positive areas.
AminusBarea = abs(AminusBarea);
BminusAarea = abs(BminusAarea);
AandBarea = abs(AandBarea);

% Output polygons: A - B
lt = zeros(AminusBn,2);
for i=1:AminusBn
  lt(i,:) = 'r-'; % plot all polygons as red and solid
end
lt = setstr(lt); % added for Matlab 5
subplot(2,2,2)
pltPolys(AminusB,AminusBIdx,AminusBn,lt)
title('Output Polygon(s) A - B')

% Output polygons: B - A
lt = zeros(BminusAn,2);
for i=1:BminusAn
  lt(i,:) = 'g-'; % plot all polygons as green and solid
end
lt = setstr(lt); % added for Matlab 5
subplot(2,2,3)
pltPolys(BminusA,BminusAIdx,BminusAn,lt)
title('Output Polygon(s) B - A')

% Output polygons: A and B
lt = zeros(AandBn,2);
for i=1:AandBn
  lt(i,:) = 'b-'; % plot all polygons as blue and solid
end
lt = setstr(lt); % added for Matlab 5
subplot(2,2,4)
pltPolys(AandB,AandBIdx,AandBn,lt)
title('Output Polygon(s) A and B')
