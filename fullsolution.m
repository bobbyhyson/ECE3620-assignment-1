
clear; clc; close all;


zi = load('y_zero_input.txt');      
zs = load('y_zero_state.txt');
yt = load('y_total.txt');

t = zi(:,1);
y_zi = zi(:,2);
y_zs = zs(:,2);
y_total = yt(:,2);


figure;
plot(t, y_zi, 'LineWidth', 1.4);
xlabel('t (s)');
ylabel('y_{zi}[n]');
title('Zero-Input Response y_{zi}[n] (From C++ Program #1)');
grid on;


y_total_sum = y_zi + y_zs;  

figure;
plot(t, y_zi, 'LineWidth', 1.2); hold on;
plot(t, y_zs, 'LineWidth', 1.2);
plot(t, y_total_sum, 'k--', 'LineWidth', 1.4);
plot(t, y_total, 'r', 'LineWidth', 1.4);

xlabel('t (s)');
ylabel('Response');
legend('Zero-input y_{zi}', 'Zero-state y_{zs}', ...
       'y_{zi} + y_{zs} (MATLAB sum)', 'Total from C++', ...
       'Location', 'Best');
title('Total Solution = Zero-input + Zero-state (C++ Results)');
grid on;


fprintf("\nPlots generated using ONLY your C++ output.\n");


t = linspace(0,10,2000);

y = -0.07294 .* exp(-2.6038 .* t) ...
    + exp(-1.1981 .* t) .* (-1.91985 .* cos(2.0797 .* t) + 0.30071 .* sin(2.0797 .* t)) ...
    - 0.01470 .* sin(2.5 * pi .* t) ...
    - 0.00721 .* cos(2.5 * pi .* t);

plot(t, y), grid on
xlabel('t'), ylabel('y(t)')
yline(0);  
