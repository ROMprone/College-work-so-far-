
%% Incarcare a datelor de tipul timeseries
clear; % sterge toate variabilele din workspace
close all; % inchide toate ferestrele de tip plot 
clc; % sterge textul din linia de comanda a MATLAB

load('data24.mat');
t=data24.Time'; % extragerea vectorului timp
sp=data24.Data(:,1)'; % extragere semnal proba
sr=data24.Data(:,2)'; % extragere raspuns sistem

% %% Afisare semnale date - Mod 1
% h1=figure('color','w'); % creare element de tip figura grafica
% plot(t,sp); % plot semnal proba
% hold on;
% plot(t,sr); % plot raspuns al sistemului
% grid on;

%% Afisare semnale date - Mod 2
h1=figure('color','w');
Lsp=line(t,sp,'Color','b');
Lsr=line(t,sr,'Color','r');
legend('Semnal proba','Raspuns sisitem');
title('Afisare semnale date');
grid on;
%% Selectare si afisare primul raspuns al sistemului
idx=(find(t<=48.95));%timpul in care apare primul raspuns al sistemului
t1=t(idx);
ysp=sp(idx);
ysr=sr(idx);
% afisare semnal primul raspuns
h2=figure('color','w');
Lysp=line(t1,ysp,'color','b');
Lysr=line(t1,ysr,'color','r');
grid on;
%% calcul valoare regim stationar
idx1=find(t1>=30);
ValRst=mean(ysr(idx1));
Lrst=line(t1,ones(size(t1))*ValRst,'color','g');
legend('Semnal proba','Raspuns sisitem','Valoare regim stationar');
title('Primul raspuns al sistemului');
%% aflare maxim si minim
MaxOsc=max(ysr);
idx2=intersect(find(t1>=2.75),find(t1<=48.95));
MinOsc=min(ysr(idx2));
%% calcul Arie A+
idxA1=intersect(find(t1>=2.75),find(t1<=9.65));

A1=0;
for i=2:length(idxA1)
    med=(( ysr(idxA1(i)) + ysr( idxA1(i-1)) )/2)-ValRst;
    A1=A1+med*(t1(idxA1(i))-t1(idxA1(i-1)));
end
%% calcul Arie A-
idxA2=intersect(find(t1>=9.65),find(t1<=16.55));
A2=0;
for i=2:length(idxA2)
    med=(( ysr(idxA2(i-1)) + ysr(idxA2(i)) )/2)-ValRst;
    A2=A2+med*(t1(idxA2(i-1))-t1(idxA2(i)));
end

%% Amplificarea
k=ValRst/sp(1:1);

%% M(raportul dintre arii)
M=A2/A1;

%% Factorul de amortizare E
n1=log(1/M);
n2=sqrt(pi^2+log(M)^2);
E=n1/n2;

%% pulsatia naturala
b1=find(sr==MaxOsc);
T1=t(b1); %timp t1
b2=find(sr==MinOsc);
T2=t(b2); %timp t2
T0=2*(T2-T1); %perioada de oscilatie
W=2*pi/(T0*sqrt(1-E^2)); %pulsatia naturala

%% functie transfer
num=(k*W^2);
den=[1 2*E*W W^2];
sys=tf(num,den); %construire functie transfer

%% raspuns la impuls
t_imp=linspace(t1(1),t1(end),numel(t1)); %face un vector pentru a genera un interval de timp între primul și ultimul element din t1
u_imp=ones(1,length(t_imp))*2.5; %face un vector cu val de 2.5 de lungimea t1 
u_imp(42:50) = 22.5; 
%y_imp=impulse(sys, t_imp)*(k); 
y_imp=lsim(sys, u_imp, t_imp); %raspuns la impuls 

%% afisare raspuns la impuls
%hold ON;
h3=figure('color','w');
L_ysr_t1=line(t1,ysr,'Color','black');
L_u_imp=line(t_imp,u_imp,'Color','blue');
L_y_imp=line(t_imp,y_imp,'Color','green');
grid ON;
legend('Raspuns sistem','Impuls','Raspuns la impuls');
title('Raspuns la impuls');

%% calcul eroare patratica 
errPatratica = 0;
for i=1:length(t_imp)
    errPatratica = errPatratica + (y_imp(i,1) - ysr(1,i))^2;
end

%% timp mort
t_mort=0;
