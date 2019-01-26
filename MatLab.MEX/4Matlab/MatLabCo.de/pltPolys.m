function pltPolys(polys,polyIdx,n,lineType)
% pltPolys - Plot polygons for one or more input polygons.
%
%Call: pltPolys(polys,polyIdx,n,lineType)
%
%Input: polys - a 2 x N sequential list of polygon vertices; N is the total count of
%               all vertices for all polygons passed in        
%       polyIdx - 1 x n vector where each element contains the number of vertices
%                 for each polygon; the sum of all these elements equals N
%       n - scalar containing the number of polygons
%       lineType - n x 2 or n x 3 vector of strings. Each string contains the graph
%                  line type for each polygon (e.g. 'r-' to plot a red solid curve)
%
%Output: Plot of polygons with passed in line type.
%
%Notes: 
%
%Gregg Leichtman, 10/29/96
%Version 1.5
%
%Modifications:
%
%Added lineType - gsl 11/1/96
%
%Removed clf - gsl 11/2/96
%
%Added ability to handle polygons that do not duplicate the first vertex
%as the last vertex - gsl 11/4/96
%
%Changed name from plotPolys to pltPolys to fit in 8.3 filename - gsl 11/8/96
%
%Added code to transpose input polygons from N x 2 to 2 x N, input index vectors
%from n x 1 to 1 x n, and line type matrices from 2 x n to n x 2 if necessary. gsl 1/17/97
%
%Added ability to handle 3 character line types. Used to only handle 2 character line
%types. gsl 3/7/97
%
%Changed max(size(...)) to length(...) to avoid warning from MatLab 5.x.
%gsl 5/12/97
%

	% Make sure vertex matrix is oriented as 2 x N.
	s = size(polys);
	if s(1) > 2
		polys = polys';
	end
	
	% Make sure index matrix is oriented as 1 x n.
	s = size(polyIdx);
	if s(1) > 1
		polyIdx = polyIdx';
	end
	
	% Make sure line type matrix is oriented as n x 2 or n x 3.
	s = size(lineType);
	if s(2) > 3
		lineType = lineType';
	end
	
	% Get total number of vertices.
	totVerts = length(polys);
		
	n = abs(n);
	
	% Initialize index for beginning of first polygon.
	j = 1;
	
	% Initialize index for end of first polygon.
	k = 0;
	
	% Allow all polygons to be plotted and visulized on the same graph.
	hold on
	
	% Cycle through each polygon.
	for i = 1:n
	
	  % Point to end of current polygon.
	  k = polyIdx(i) + k;
	  
	  % Make sure last vertex equals first vertex.
	  if any(polys(:,j) ~= polys(:,k))
	  
	    % Insert a new vertex.
	    polysTmp = [polys(:,1:k) polys(:,j)];
		
		% Tack on any remaining unprocessed polygons.
		if k < totVerts
	      polysTmp = [polysTmp polys(:,k+1:totVerts)];
		end
		polys = polysTmp;
		
		% Count new vertex.
		totVerts = totVerts + 1;
		k = k + 1;
	  end

	  % Plot current polygon.
	  plot(polys(1,j:k),polys(2,j:k),lineType(i,:))
	  
	  % Point to beginning of next polygon.
	  j = k + 1;
	end
	hold off

%end plotPolys
