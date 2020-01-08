% target = rgb2gray(imread('target.jpg'));
% shot = target(250:300, 435:480);
% target = imresize(target, 0.4);
% shot = imresize(shot, 0.4);
% c = normxcorr2(shot, target);
% [vals, yIdx] = max(c);
% [vals, xIdx] = maxk(vals, 5);
% yIdx = yIdx(xIdx);
% figure
% imshow(target)
% [x_offset, y_offset] = size(shot);
% x_offset = x_offset/2;
% y_offset = y_offset/2;
% 
% for i=1:20
%     [vals, y_idx] = max(c);
%     [val, x_idx] = max(vals);
%     x_idx = x_idx;
%     y_idx = y_idx(x_idx);
%     hold on
%     plot(x_idx-x_offset, y_idx-y_offset, 'r*','linewidth', 25, 'MarkerSize', 10)
%     c((y_idx-5):(y_idx+5), (x_idx-5):(x_idx+5)) = 0;
% end
% figure
% surf(c)
% shading flat
