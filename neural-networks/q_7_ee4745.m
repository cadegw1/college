clear
%--- Part(i)
[X,Y] = meshgrid(-0.2 : .01 : .5);
F = 3*(X.^2+Y.^2) - 2*X.*Y - X - Y;
N = 10;
x0 =[.125 -.125]';
figure;
plot(x0(1), x0(2),'r*')
hold on;
contour(X,Y,F,N)
title('Fig.2 Trajectory for steepest descent for E9.2'); 
xlabel('X1 axis'), ylabel('X2 axis');
%---

A = [6 -2;-2 6];
d = [-1;1];
alfa = 0.01;

%Find the eigenvalues and eigenvecors of Hessian matrix
[V,D] = eig(A);

iter = 0;
x = [0 0]';   %Initialize x

%Find the stationary point
G = A*x + d;
small = [1.0e-4 1.0e-4]';

while (abs(G(1)) >= small(1) || abs(G(2))>= small(2))
	plot(x(1), x(2),'k.')
	x = x - alfa * G;
	G = A*x + d;
	iter = iter + 1;   
	if (iter == 2)
   	x2 = x;   %Output the x value after two iterations
	end
end
x;   %Output the stationary point
hold off;  
