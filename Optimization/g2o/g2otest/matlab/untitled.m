
clc; close all; clear;
A = load('out_t.txt');
B = load('out_loopclosure_from+to.txt');
idx = 1:size(A, 1);
idxsparse = GetSparseIDX(idx, 5);

% default values
nodesPerLevel = 50;
numLaps = 50;

H = zeros(4,4,size(A,1));
for i=1:size(A,1)
   row  = A(i,:);
   m    = reshape(row, 4,4)';
   H(:,:,i) = m; 
   
end
%% half of the data generated 
draw_lc_edge = 2;
if draw_lc_edge ==1,
    figure;
    plot3(H(1,4,1), H(2,4,1), H(3,4,1),'r*'); 

    axis equal;
    xlabel('X');
    ylabel('Y');
    zlabel('Z');
    view(-28,60);
    grid on;
    hold on;
    %for i=1:size(A,1) -1  
    for i=1:size(A,1)/2%-1
        X = [H(1,4,i),   H(2,4,i),   H(3,4,i);
             H(1,4,i+1), H(2,4,i+1), H(3,4,i+1)];
        plot3(X(:,1,:), X(:,2,:), X(:,3,:),'b.-'); 

    end

    % for visualization purposes
    % https://kr.mathworks.com/matlabcentral/newsreader/view_thread/22293
    ct = [14.1611   24.9349   49.9371];
    cva = 0.6785;

    set(gca, 'CameraTarget', ct);
    set(gca, 'CameraViewAngle', cva);

    for i=1:size(B,1)/2
        X = [B(i,1),     B(i,2),     B(i,3);
             B(i,5),     B(i,6),     B(i,7)];
        plot3(X(:,1,:), X(:,2,:), X(:,3,:),'r-'); 
        plot3(X(1,1,:), X(1,2,:), X(1,3,:),'ro'); 
        %k = waitforbuttonpress;

    end

elseif draw_lc_edge ==2, % One per laps
    figure;
    plot3(H(1,4,1), H(2,4,1), H(3,4,1),'r*'); 

    axis equal;
    xlabel('X');
    ylabel('Y');
    zlabel('Z');
    view(-28,60);
    grid on;
    hold on;
    %for i=1:size(A,1) -1  
    for i=1:size(A,1)/2
        X = [H(1,4,i),   H(2,4,i),   H(3,4,i);
             H(1,4,i+1), H(2,4,i+1), H(3,4,i+1)];
        plot3(X(:,1,:), X(:,2,:), X(:,3,:),'b.-'); 

    end

    for i=1:nodesPerLevel*3:size(B,1)/2
        if i>2 
            for j=0:2,

            X = [B(i+j,1),     B(i+j,2),     B(i+j,3);
                 B(i+j,5),     B(i+j,6),     B(i+j,7)];
            plot3(X(:,1,:), X(:,2,:), X(:,3,:),'r-'); 
            plot3(X(1,1,:), X(1,2,:), X(1,3,:),'ro'); 
            %k = waitforbuttonpress;
            end
        end
    end

   
    
end

%%
A = A(idxsparse, :);
H = zeros(4,4,size(A,1));
for i=1:size(A,1)/2
   row  = A(i,:);
   m    = reshape(row, 4,4)';
   H(:,:,i) = m; 
   
end

%% half of the data generated (with some strides)
figure;
%for i=1:size(A,1)-1
plot3(H(1,4,1), H(2,4,1), H(3,4,1),'r*'); 
hold on;
for i=1:size(A,1)/2    
    X = [H(1,4,i),   H(2,4,i),   H(3,4,i);
         H(1,4,i+1), H(2,4,i+1), H(3,4,i+1)];
    plot3(X(:,1,:), X(:,2,:), X(:,3,:),'b.-'); 
    
end

axis equal;
xlabel('X');
ylabel('Y');
zlabel('Z');
grid on;

%%
figure;
g = 5;
plot3(H(1,4,1), H(2,4,1), H(3,4,1),'b+'); 
hold on;
idxlast = size(A,1);
plot3(H(1,4,idxlast), H(2,4,idxlast), H(3,4,idxlast),'bo'); 


for i=1:size(A,1)
    %plot3(H(1,4,i), H(2,4,i), H(3,4,i),'b.'); 
    quiver3(H(1,4,i), H(2,4,i), H(3,4,i), g*H(1,1,i), g*H(2,1,i), g*H(3,1,i), 'Color', [1 0 0]);
    quiver3(H(1,4,i), H(2,4,i), H(3,4,i), g*H(1,2,i), g*H(2,2,i), g*H(3,2,i), 'Color', [0 1 0]);
    quiver3(H(1,4,i), H(2,4,i), H(3,4,i), g*H(1,3,i), g*H(2,3,i), g*H(3,3,i), 'Color', [0 0 1]);   
end;
axis equal;
xlabel('X');
ylabel('Y');
zlabel('Z');

grid on;