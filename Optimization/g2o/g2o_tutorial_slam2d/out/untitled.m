clc; clear; close all;
A = load('poses.txt');
l = load('landmarks.txt');
lo = load('landmarks_obs.txt');

%%
figure;
% plot(A(:, 1), A(:, 2),'.-');
% hold on;
% plot(A(:, 3), A(:, 4),'.-');
boundArea = 50-0;

bPause = 0;
npose = size(A, 1);

for i=1:size(A, 1)-1
    X1 = [A(i, 1), A(i, 2); ;A(i+1, 1), A(i+1, 2)];
    X2 = [A(i, 3), A(i, 4); ;A(i+1, 3), A(i+1, 4)];
   
    plot(X1(:,1), X1(:, 2),'.-', 'color', [0 0 1 ]); hold on;
    plot(X2(:,1), X2(:, 2),'.-', 'color', [1 0 1 ]);
    
    
    if bPause==1,
        pause(0.05);
    end
    
    if i==1,
        xlim([-boundArea, boundArea]);
        ylim([-boundArea, boundArea]);
        grid on;
        legend('true pose', 'simulated pose');
        %axis equal;
    end
    buf = sprintf('# of poses : %d', i);
    title(buf);
end

plot(A(1,1), A(1,2), '*', 'color', [0 0 0 ]);
quiver(A(1,1), A(1,2), A(2,1) -  A(1,1),  A(2,2) -  A(1,2), 2, 'color', [0 0 0 ]);

%% Connection
figure;
ndisp = npose;

for i=1:ndisp-1
    X1 = [A(i, 1), A(i, 2); A(i+1, 1), A(i+1, 2)];
    X2 = [A(i, 3), A(i, 4); A(i+1, 3), A(i+1, 4)];
   
    %plot(X1(:,1), X1(:, 2),'.-', 'color', [0 0 1 ]); hold on;
    plot(X2(:,1), X2(:, 2),'.-', 'color', [1 0 1 ]); hold on;
    
    plot(A(1,1), A(1,2), '*', 'color', [0 0 0]);


    idx = find(l(:,1) == i);
    
    if size(idx, 1)<1,
        continue;
    end
    
    for j=1:size(idx, 1),
        X1 = [A(i, 3) A(i, 4); l(idx(j, 1), 2+2) l(idx(j, 1), 3+2)];
        plot(X1(:,1), X1(:, 2), '-', 'color', [0.5 0.5 0.5 0.3]);
        plot(l(idx(j, 1), 2+2), l(idx(j, 1), 3+2), '.', 'color', [0 0 1]);
    end
    
    xlim([-boundArea, boundArea]);
    ylim([-boundArea, boundArea]);
    %pause(0.1);
end
title ('landmarks generated');

%%
figure;
plot(A(:,1), A(:,2), '.-', 'color', [0 0 1 ]); hold on;
plot(A(:,3), A(:,4), '.-', 'color', [1 0 1 ]); 
plot(A(1,1), A(1,2), '*', 'color', [0 0 0]);

plot(l(:,4), l(:,5), '.');

xlim([-boundArea, boundArea]);
ylim([-boundArea, boundArea]);
grid on;
legend('true pose', 'simulated pose');
axis equal;


%% Connection (observation)

figure;
nlandmarks = size(lo, 1);
ndisp = nlandmarks;%/5;
maxConnection = 30; % See simulator.cpp

%plot(A(:,1), A(:,2), '.-', 'color', [0 0 1 ]); hold on;
plot(A(:,3), A(:,4), '.-', 'color', [1 0 1 ]);  hold on;
plot(A(1,1), A(1,2), '*', 'color', [0 0 0]);

% xlim([-boundArea, boundArea]);
% ylim([-boundArea, boundArea]);

xlim([-5, 35]);
ylim([-15, 25]);
    

for i=1:ndisp-1
    plot(lo(i, 2), lo(i,3),'.', 'color', [0 0 1]);
    
   
    for j=1:maxConnection
        if lo(i, 3+j) <0,
            break;
        end
        
        idxpose = find(A(:, 5) == lo(i, 3+j));
        
        X1 = [A(idxpose, 3), A(idxpose, 4); lo(i, 2), lo(i,3)];
        plot(X1(:,1), X1(:, 2), '-', 'color', [0.5 0.5 0.5 0.3]);
        
    end
    
    pause(0.1);
end
title ('landmarks simulated');



