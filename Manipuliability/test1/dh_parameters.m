%%% DENAVIT HARTENBERG Parameteres by Mahmoud KhoshGoftar%%%
clear all
close all
clc
prompt = {'Enter how many robot arms?'};
dlg_title = 'Input';
num_lines = 1;
def = {'1'};
answer = inputdlg(prompt,dlg_title,num_lines,def);
num = str2num(answer{:});
F = sym('A', [num 4]);
B=eye(4);
C = sym('C', [4 4]);
clc
for i=1:num
    prompt = {'Enter a:','Enter alfa:','Enter d:','Enter theta:'};
    dlg_title = sprintf('arm%d',i);
    num_lines = 1;
    def1 = {sprintf('a%d',i),sprintf('alfa%d',i),sprintf('d%d',i),sprintf('t%d',i)};
    answer1 = inputdlg(prompt,dlg_title,num_lines,def1);
    F(i,1)=answer1(1,1);
    F(i,2)=answer1(2,1);
    F(i,3)=answer1(3,1);
    F(i,4)=answer1(4,1);
    C=simplify([cos(F(i,4)) -sin(F(i,4))*cos(F(i,2)) sin(F(i,4))*sin(F(i,2)) F(i,1)*cos(F(i,4));
             sin(F(i,4)) cos(F(i,4))*cos(F(i,2)) -cos(F(i,4))*sin(F(i,2)) F(i,1)*sin(F(i,4));
             0 sin(F(i,2)) cos(F(i,2)) F(i,3);
             0 0 0 1]);
    eval(sprintf('A%d = C;',i));
    B=B*C;
    eval(sprintf('A%d',i))
end
sprintf('T from Arm 0 to Arm %d is:',i)
pretty(simplify(B))
'R is Rotation Matrix'  , R=B(1:3,1:3);
pretty(R)
d=B(1:3,4);
'd is translation Matrix' , pretty(d)


   
   