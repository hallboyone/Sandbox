img = imread('camera_man_gray.png');
e = edge(img, 'canny');
[h, t, r] = hough(e);
p = houghpeaks(h, 20, 'NHoodSize', [25,25]);
imshow(h,[],'XData',t,'YData',r,'InitialMagnification','fit');
xlabel('\theta'), ylabel('\rho');
axis on, axis normal, hold on;
plot(t(p(:,2)),r(p(:,1)),'s','color','white');

p(:,2) = pi*t(p(:,2))/180;
p(:,1) = r(p(:,1));

figure
imshow(e,[],'InitialMagnification','fit');
hold on
%plot([p(1, 1)/cos(p(1,2)) 0], [0, p(1, 1)/sin(p(1,2))])
for i=1:18
    x_intercept = p(i, 1)/cos(p(i,2));
    y_intercept = -p(i, 1)/sin(p(i,2));
    slope = y_intercept/x_intercept;
    y_vals = (0:500)*slope - y_intercept;
    line([0:500]', y_vals')
    %[p(i, 1)/cos(p(i,2)) 0], [0, -p(i, 1)/sin(p(i,2))]
end
%surf(hough(e))
%shading flat