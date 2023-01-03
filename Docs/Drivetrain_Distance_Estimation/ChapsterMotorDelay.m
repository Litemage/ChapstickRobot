% Test conducted & data collected on 12/31/22

% Used to perform calculations mapping motor percent output and
%   distance to a delay for chapstick robot

% 3 Tests were performed to estimate how many ms it takes for the robot to reach
%   30cm, those times were logged and the test was ran 3 times

% Speeds data collected at, 0-0.3 missing because motors don't move
%   at those speeds due to low torque, so they are left out
x = [0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1];

%data collected. ms delay it takes to reach 30cm
y1 = [1050, 850, 700, 650, 600, 545, 510];
y2 = [1150, 850, 700, 640, 580, 545, 500];
y3 = [1115, 850, 720, 645, 600, 545, 500];

y = mean([y1; y2; y3]);

% Increase default font size
%figure('DefaultAxesFontSize', 18);

% Visualize raw data
subplot(2, 2, 1);
hold on;
plot(x, y1, "-ro"); xlabel("Percent motor output"); ylabel("Time to reach 30cm (ms)");
plot(x, y2, "-bo");
plot(x, y3, "-go");
legend("Test 1", "Test 2", "Test 3");
hold off;
title("Collected Data");

% Visualize the mean data of all 3 tests
subplot(2,2,2);
plot(x, y, "--m"); xlabel("Percent motor output"); ylabel("Time to reach 30cm (ms)");
title("Mean of all data");

% Plot the linear approximation of speed/delay to 30cm map
subplot(2,2,3);
[P1,S1] = polyfit(x, y, 1);
yApproxLin = polyval(P1, x);
plot(x, yApproxLin, "--k"); xlabel("Percent motor output"); ylabel("Time to reach 30cm (ms)");
legend(sprintf("(%d)x + (%d)", P1(1), P1(2)));
title("Linear approximation of speed/delay to 30cm map");

% Plot 2nd degree polynomial approximation
subplot(2,2,4);
[P2, S2] = polyfit(x, y, 2);
yApproxPoly = polyval(P2, x);
plot(x, yApproxPoly, "--k"); xlabel("Percent motor output"); ylabel("Time to reach 30cm (ms)");
legend(sprintf("(%d)x^2 + (%d)x + (%d)", P2(1), P2(2), P2(3)));
title("2nd degree polynomial approximation of speed/delay to 30cm map");

%display functions
fprintf("Linear Approximation: (%i)x + (%i)\n", P1(1), P1(2));
fprintf("2nd Degree Polynomial Approximation:(%i)x^2 + (%i)x + (%i)\n", P2(1), P2(2), P2(3));
