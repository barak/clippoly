function plotMClp(polyA,polyAIdx,polyAn,polyB,polyBIdx,polyBn)
% plotMClp - Take two sets of polygons, run through all combinations of pairs, clip
%            them against each other, and then plot the three
%            clipped regions---A - B, B - A, A and B---in turn for each pair.
%            Also calculate the total area across all polygon pairs for
%            A - B, B - A, and A & B. gsl 11/4/96
%
%Input: polyX - a 2 x N sequential list of polygon vertices; N is the total count of
%               all vertices for all polygons passed in        
%       polyXidx - 1 x n vector where each element contains the number of vertices
%                  for each polygon; the sum of all these elements equals N
%       polyXn - scalar containing the number of polygons
%
%Output: Plot of multiple clipped polygon pairs.
%
%Notes: 
%
% If the polygons polyA and polyB are not loaded in the workspace, use
% a default pair that forms the Star of David.
% I have included other polygon pairs that you can load with the command
% load FILENAME
% where FILENAME is one of case1, case2, case3 or in_file. You can also
% use the Load Workspace... command in the file menu to accomplish the
% same thing. gsl
%
% WARNING: This code will not calculate the areas properly if
%          the A polygons overlap each other or the B polygons overlap
%          each other. Portions of the overlapping areas will be added more
%          than once.
%          The way around this difficulty is to pass the A polygons through
%          the clipping code and take the output as the true A input polygons
%          and repeat this for the B polygons. This way only disjoint
%          polygons are passed into the polygon clipper.
%          If more than two polygons overlap in any portion of the plane,
%          it is necessary to iterate until no polygons remain that
%          overlap each other. gsl
%
%
%Gregg Leichtman, 11/4/96
%Version 1.4
%
%Modifications:
%
% Converted from a MatLab script to a function. - gsl 1/15/97 
%
% Changed A & B polygon output color from white to blue. - gsl 1/23/97
%
% Fixed bugs in indexing through each polygon to be clipped. - gsl 2/12/97
%
% Added "lt = setstr(lt);" after setting each line type. Matlab 5.x
% needed explicit statement to force matrix into a string type.
% gsl 5/12/97
%

%'Loading input polygons...'
if (~ exist('polyA')) | (~ exist('polyAIdx')) | (~ exist('polyAn'))
  polyA = [1     0     2     1; ...
          -1     1     1    -1]
  % Could also use:
  %polyA = [1     0     2; ...
  %        -1     1     1]
  %polyAIdx = 3; % Number of vertices per polygon.
  polyAIdx = 4; % Number of vertices per polygon.
  polyAn = 1;   % Number of polygons.
end
if (~ exist('polyB')) | (~ exist('polyBIdx')) | (~ exist('polyBn'))
  polyB = [0     1     2     0; ...
           0     2     0     0]
  % Could also use:
  %polyB = [0     1     2; ...
  %         0     2     0]
  %polyBIdx = 3; % Number of vertices per polygon.
  polyBIdx = 4; % Number of vertices per polygon.
  polyBn = 1;   % Number of polygons.
end

% Initialize starting and ending indices of each polygon's vertices.
sA = 1;
eA = 0;
sB = 1;
eB = 0;

% Initialize total areas for A - B, B - A, and A & B.
AminusBareaTot = 0;
BminusAareaTot = 0;
AandBareaTot = 0;

% Display all input polygon pairs: A, B
totPolys = polyAn + polyBn;
lt = zeros(totPolys,2);
for i=1:polyAn
  lt(i,:) = 'r-'; % plot all A polygons as red and solid
end
lt = setstr(lt);
offset = polyAn + 1;
for i=offset:totPolys
  lt(i,:) = 'g-'; % plot all B polygons as green and solid
end
lt = setstr(lt);

% Clear the figure and plot.
clf
pltPolys([polyA polyB],[polyAIdx polyBIdx],polyAn + polyBn,lt)
title('All Input Polygon Pairs A (Red) and B (Green)')
disp('Press a key to continue...')
pause

% Run through all combinations of the polygon pairs.
for ii = 1:polyAn

  % Point to last vertex of current polygon A.
  eA = polyAIdx(ii) + eA;
  
  for jj = 1:polyBn
  
    % Point to last vertex of current polygon B.
    eB = polyBIdx(jj) + eB;
	
		% Extract current polygon A and polygon B from list.
		pA = polyA(:,sA:eA);
		pB = polyB(:,sB:eB);
		
		% Clip the polygon pair.
		disp('Clipping polygons...')
		[AminusB,AminusBidx,AminusBn,AminusBarea, ...
		 BminusA,BminusAidx,BminusAn,BminusAarea, ...
		 AandB,AandBidx,AandBn,AandBarea]=clippoly(pA,pB);
		
		% Point to first vertex of next polygon B.
		sB = sB + polyBIdx(jj);
		
		% The sign of the area indicates the clockwise-negative sign-or counter-clockwise-positive
		% sign-ordering of the polygon vertices. For this application, output only positive areas.
		%AminusBarea = abs(AminusBarea)
		%BminusAarea = abs(BminusAarea)
		%AandBarea = abs(AandBarea)
		
		% Total up the areas across all polygon pairs.
		AminusBareaTot = AminusBareaTot + sum(abs(AminusBarea));
		BminusAareaTot = BminusAareaTot + sum(abs(BminusAarea));
		AandBareaTot = AandBareaTot + sum(abs(AandBarea));
		
		disp('Plotting...')
		
		% Clear figure.
		clf
		
		% Input polygons: A, B
		subplot(2,2,1)
		pltPolys([pA pA(:,1) pB pB(:,1)],[max(size(pA))+1 max(size(pB))+1],2,['r-'; 'g-'])
		title('Input Polygons A (Red) and B (Green)')
		
		% Output polygons: A - B
		lt = zeros(AminusBn,2);
		for i = 1:AminusBn
		  lt(i,:) = 'r-'; % plot all polygons as red and solid
		end
		lt = setstr(lt);
		subplot(2,2,2)
		pltPolys(AminusB,AminusBidx,AminusBn,lt)
		title('Output Polygon(s) A - B')
		
		% Output polygons: B - A
		lt = zeros(BminusAn,2);
		for i = 1:BminusAn
		  lt(i,:) = 'g-'; % plot all polygons as green and solid
		end
		lt = setstr(lt);
		subplot(2,2,3)
		pltPolys(BminusA,BminusAidx,BminusAn,lt)
		title('Output Polygon(s) B - A')
		
		% Output polygons: A and B
		lt = zeros(AandBn,2);
		for i = 1:AandBn
		  lt(i,:) = 'b-'; % plot all polygons as blue and solid
		end
		lt = setstr(lt);
		subplot(2,2,4)
		pltPolys(AandB,AandBidx,AandBn,lt)
		title('Output Polygon(s) A and B')
		
		if (max([polyAn polyBn]) > 1) & ((ii ~= polyAn) | (jj ~= polyBn))
		  disp('Press a key to continue...')
		  pause
		end
  end % cycling through B polygons

  % Point to first vertex of next polygon A.
  sA = sA + polyAIdx(ii);
	
  % Re-initialize starting and ending indices of B polygon's vertices.
  sB = 1;
  eB = 0;

end % cycling through A polygons

% Display the total areas across all polygon pairs.
AminusBareaTot
BminusAareaTot
AandBareaTot

disp('Done.')
