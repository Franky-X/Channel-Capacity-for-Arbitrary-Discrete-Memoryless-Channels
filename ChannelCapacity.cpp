

#include <iostream>
#include <cmath>

int main()
{
    std::cout << "This is a program for Channel Compacity Computation \n";
    // assign channel matrix
    double P[3][3];
    P[0][0] = 0.6;
    P[0][1] = 0.7;
    P[0][2] = 0.5;
    P[1][0] = 0.3;
    P[1][1] = 0.1;
    P[1][2] = 0.05;
    P[2][0] = 0.1;
    P[2][1] = 0.2;
    P[2][2] = 0.45;
    std::cout << "Channel Matrix:\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << P[i][j] << " ";
            if (j == 2)
            {
                std::cout << std::endl;
            }
        }
    }

    // Iteration Algorithm
    // Step 1: assign initial value
    double px[3] = { 1 / 3.0, 1 / 3.0, 1 / 3.0 };
    std::cout << "Initial Input PMF: \n";
    for (int i = 0; i < 3; i++)
    {
        std::cout << px[i]<< " ";
    }
    std::cout << std::endl;

    double phi[3][3] = {0};
    double px_next[3] = {0};
    double C_tt = 0;
    double C_t1t = 100;


    // Step 2: Compute phi^t
    while (abs(C_t1t - C_tt) > 0.00001)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                double pi = 0;
                for (int k = 0; k < 3; k++)
                {
                    pi += P[i][k] * px[k];
                }
                phi[j][i] = (P[i][j] * px[j]) / pi;
            }
        }

        double HX = 0;
        double HXY = 0;
        for (int i = 0; i < 3; i++)
        {
            HX += -px[i] * std::log2(px[i]);
        }

        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 3; i++)
            {
                HXY += -P[i][j] * px[j] * std::log2(phi[j][i]);
            }
        }
        C_tt = HX - HXY;
        // std::cout << C_tt << std::endl;
        // Step 3: Compute px_next
        double r[3] = { 1,1,1 };
        for (int j = 0; j < 3; j++)
        {
            // double sum = 0;
            for (int i = 0; i < 3; i++)
            {
                r[j] *= std::exp2(P[i][j] * std::log2(phi[j][i]));
            }
            // r[j] = std::exp(sum);
        }

        double r_sum = 0;
        for (int k = 0; k < 3; k++)
        {
            r_sum += r[k];
        }

        for (int j = 0; j < 3; j++)
        {
            px[j] = r[j] / r_sum;
            // std::cout << px[j] << "\t";
        }
        std::cout << px[2] << std::endl;
        HX = 0;
        HXY = 0;
        for (int i = 0; i < 3; i++)
        {
            HX += -px[i] * std::log2(px[i]);
        }

        double temp = 0;
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 3; i++)
            {
                // temp += -std::log(r[i]);
                temp += -P[i][j] * std::log2(phi[j][i]);
;           }
            //temp += -std::log2(r[j]);
            temp *= px[j];
            HXY += temp;
        }

        C_t1t = HX - HXY;
        // std::cout << C_t1t << std::endl;
    }
}

