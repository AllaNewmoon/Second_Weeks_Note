function x = spin_vector(vec, b)
c = [cos(b) -sin(b);sin(b) cos(b)];
x = c*(vec');
disp(x');
