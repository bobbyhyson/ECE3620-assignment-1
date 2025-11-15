#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

const double PI = 3.14159265358979323846;


void mattimes(double dt, const double A[3][3], double result[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            result[i][j] = dt * A[i][j];
}

void matadd(const double A[3][3], const double B[3][3], double C[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            C[i][j] = A[i][j] + B[i][j];
}

void matvecmult(const double M[3][3], const double v[3], double prod[3]) {
    for (int i = 0; i < 3; ++i) {
        prod[i] = 0.0;
        for (int j = 0; j < 3; ++j) {
            prod[i] += M[i][j] * v[j];
        }
    }
}

std::vector<double> conv(const std::vector<double>& x,
                         const std::vector<double>& h) {
    int n = static_cast<int>(x.size());
    int m = static_cast<int>(h.size());
    std::vector<double> y(n + m - 1, 0.0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            y[i + j] += x[i] * h[j];
        }
    }
    return y;
}

std::vector<double> sample_h(double T, int N) {
    std::vector<double> h(N + 1);

    const double A1    = -0.175169590900698;
    const double p1    = -2.60381515752759;

    const double alpha = -1.198092421236205;
    const double beta  =  2.079748094628012;
    const double a     =  0.0875847954503492;
    const double b     =  0.1812142839103903;

    for (int k = 0; k <= N; ++k) {
        double t = k * T;
        double term1 = A1 * std::exp(p1 * t);
        double term2 = 2.0 * std::exp(alpha * t) *
                       (a * std::cos(beta * t) - b * std::sin(beta * t));
        h[k] = term1 + term2;
    }
    return h;
}

std::vector<double> sample_f(double T, int N) {
    std::vector<double> f(N + 1);
    const double omega = 2.5 * PI;

    for (int k = 0; k <= N; ++k) {
        double t = k * T;
        f[k] = std::sin(omega * t);
    }
    return f;
}

std::vector<double> compute_zero_input(double Tfinal, double dt) {
    int N = static_cast<int>(Tfinal / dt);

    double A[3][3] = {
        {  0.0,  1.0,  0.0 },
        {  0.0,  0.0,  1.0 },
        { -15.0, -12.0, -5.0 }
    };

    double I[3][3] = {
        { 1.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 1.0 }
    };

    double dtA[3][3];
    double phi[3][3];

    mattimes(dt, A, dtA);
    matadd(I, dtA, phi);

    double v[3]     = { -2.0, 3.0, 4.0 };
    double vnext[3] = { 0.0, 0.0, 0.0 };

    std::vector<double> y_zi(N + 1);

    for (int k = 0; k <= N; ++k) {
        y_zi[k] = v[0];
        matvecmult(phi, v, vnext);
        v[0] = vnext[0];
        v[1] = vnext[1];
        v[2] = vnext[2];
    }

    return y_zi;
}
int main() {
    double Tfinal = 10.0;
    double T      = 0.001;
    int    N      = static_cast<int>(Tfinal / T);

    std::vector<double> y_zi = compute_zero_input(Tfinal, T);

    std::vector<double> h = sample_h(T, N);

    std::vector<double> f = sample_f(T, N);

    std::vector<double> conv_fh = conv(f, h);
    std::vector<double> y_zs(N + 1);
    for (int n = 0; n <= N; ++n) {
        y_zs[n] = T * conv_fh[n];
    }

    std::vector<double> y_total(N + 1);
    for (int n = 0; n <= N; ++n) {
        y_total[n] = y_zi[n] + y_zs[n];
    }
    {
        std::ofstream out("h_samples.txt");
        double t = 0.0;
        for (int n = 0; n <= N; ++n) {
            out << t << " " << h[n] << "\n";
            t += T;
        }
    }

    {
        std::ofstream out("f_samples.txt");
        double t = 0.0;
        for (int n = 0; n <= N; ++n) {
            out << t << " " << f[n] << "\n";
            t += T;
        }
    }

    {
        std::ofstream out("y_zero_input.txt");
        double t = 0.0;
        for (int n = 0; n <= N; ++n) {
            out << t << " " << y_zi[n] << "\n";
            t += T;
        }
    }

    {
        std::ofstream out("y_zero_state.txt");
        double t = 0.0;
        for (int n = 0; n <= N; ++n) {
            out << t << " " << y_zs[n] << "\n";
            t += T;
        }
    }

    {
        std::ofstream out("y_total.txt");
        double t = 0.0;
        for (int n = 0; n <= N; ++n) {
            out << t << " " << y_total[n] << "\n";
            t += T;
        }
    }

    std::cout << "Done. Files written:\n"
              << "  h_samples.txt\n"
              << "  f_samples.txt\n"
              << "  y_zero_input.txt\n"
              << "  y_zero_state.txt\n"
              << "  y_total.txt\n";

    return 0;
}

