clc;
clear;
close all;
rawTable = readtable('testData.xlsx','Sheet','Sheet1');
x = rawTable.Time;
y = rawTable.Thrust;
z = rawTable.Chamber_Pressure;

burn_time= 3.6;
disp('Burn Time= ');
disp(burn_time);
        
max_thrust=max(y);
disp('Max Thrust= ');
disp(max_thrust);

avg_thrust=mean(x);
disp('Average Thrust= ');
disp(avg_thrust);

tot_imp=avg_thrust*burn_time;
disp('Total Impulse= ');
disp(tot_imp);

Chamber_Pressure=max(z);
disp('Chamber Pressure');
disp(Chamber_Pressure);

figure;
plot(x,y,x,z);
title('Thrust v/s Time');
xlabel('Time in Secs');
ylabel('Thrust in Newtons & Chamber Pressure in Pascals');
