function [pArea] = polyArea(poly)
%
%polyArea - calculate the area of a planar polygon given its vertices.
%
%Call: [pArea] = polyArea(poly)
%
%Input: 	poly - 2 x N or N x 2 list of vertices
%
%Output:
%			pArea - the area of the polygon
%
%Notes: Polygon cannot be self-intersecting.  No check is made for this.
%
%				If the polygon is 2 x 2, then each column is assumed to be a vertex.
%
%				No check is made to insure that the matrix passed in is 2 x N or N x 2.
%
%				The sign of the area passed out indicates the direction of traversal
%				of the vertices.
%
%       The first vertex of the polygon can but is not required to be duplicated
%       as the last vertex.
%
%Gregg Leichtman, 12/3/96
%Version 1.0
%
%Modifications:
%

  % Make the shape 2 x N if N x 2. In the interest of speed, no check 
	% is made to see if poly is one of these sizes.
	chk = size(poly);
	if chk(1) ~= 2
	  poly = poly';
	end

  % Extract number of vertices passed in.
	n = max(size(poly));

  % If last vertex equals the first one, don't use it in calculations.
	if poly(:,1) == poly(:,max(chk))
    n = n - 1;
	end
	
	% Initialize the polygon area. Sign indicates that traversal was either
	% clockwise or counter-clockwise.
	pArea = 0;
	% Calculate the area of the polygon. Polygon cannot be self-intersecting.
	% See Foley, van Dam, Feiner and Hughes, Computer Graphics Principles and Practice,
	% Addison Wesley, 2nd. ed., pg. 1112.
	for i = 1:n
    pArea = pArea + poly(1,i) * poly(2,rem(i,n) + 1) - poly(1,rem(i,n) + 1) * poly(2,i);
	end
  pArea = pArea / 2;
