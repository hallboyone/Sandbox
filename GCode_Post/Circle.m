classdef Circle
   properties
       radius;
       c_x;
       c_y;
   end
   
   methods
       function obj = Circle(arr)
           obj.radius = arr(3);
           obj.c_x = arr(1);
           obj.c_y = arr(2);
       end
       
       function plot(obj)
           o = linspace(0, 2*pi);
           plot(obj.c_x + obj.radius * cos(o), obj.c_y + obj.radius * sin(o), 'k-');
       end
       
       function zVals = plotFun(obj, fun)
           [X, Y] = obj.getVals();
           zVals = zeros(size(X));
           for i=1:numel(X)
               zVals(i) = fun([X(i);Y(i)]);
           end
           plot3(X, Y, zVals, 'k-');
       end
       
       function [xVals, yVals] = getVals(obj)
           o = linspace(0, 2*pi);
           xVals = obj.c_x + obj.radius * cos(o);
           yVals = obj.c_y + obj.radius * sin(o);
       end
   end
end