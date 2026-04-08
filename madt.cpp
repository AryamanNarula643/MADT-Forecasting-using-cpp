#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    // Data for 19 months provided in the table
    vector<double> madt = {
        852, 861, 958, 1037, 1045, 1109, 1117, 1134, 1236,
        1077, 868, 997, 962, 907, 1098, 1167, 1232, 1277, 1349
    };

    int n = madt.size();

    cout << fixed << setprecision(2);

    // Calculate 3-month moving average
    cout << "Calculating 3-month moving averages..." << endl;
    
    // Outputting the moving average forecast for months where it can be calculated
    for (int i = 3; i < n; ++i) {
        double ma = (madt[i - 1] + madt[i - 2] + madt[i - 3]) / 3.0;
        cout << "Month " << i + 1 << " -> " << ma << endl;
    }
    
    // Forecast for the 20th month
    double forecast_20_ma = (madt[n - 1] + madt[n - 2] + madt[n - 3]) / 3.0;
    cout << "\nSo, the MA forecast for month 20 is: " << forecast_20_ma << "\n\n";

    
    // Exponential smoothing part
    double alpha;
    cout << "What alpha value should we use? (0.0 to 1.0): ";
    
    // Note: When running this program, you must provide an input for alpha in the console.
    if (!(cin >> alpha)) {
        alpha = 0.3; // Default fallback if no input is provided or reading fails
        cout << "\nCouldn't read that. Using 0.3 as the default alpha." << endl;
    }

    cout << "\nRunning exponential smoothing...\n" << endl;

    vector<double> exp_smooth(n + 1, 0.0);
    exp_smooth[0] = madt[0]; // Assume initial forecast F_1 equals actual D_1
    
    for (int i = 1; i <= n; ++i) {
        exp_smooth[i] = alpha * madt[i - 1] + (1.0 - alpha) * exp_smooth[i - 1];
        if(i < n) {
            cout << "Month " << i + 1 << " -> " << exp_smooth[i] << endl;
        }
    }

    double forecast_20_es = exp_smooth[n];
    cout << "\nES forecast for month 20 comes out to: " << forecast_20_es << "\n\n";


    // Final thoughts and justification
    cout << "Which method is better here?\n";
    cout << "I'd definitely go with Exponential Smoothing for this dataset.\n";
    cout << "A basic moving average is a bit too rigid. It treats the last three months exactly the same\n";
    cout << "and completely ignores everything before that, which means it lags way behind when the\n";
    cout << "numbers start trending up.\n\n";
    cout << "ES makes more sense because it weights the recent data heavier while still keeping\n";
    cout << "a memory of the older data in the background. If you look at the end of the dataset, the\n";
    cout << "traffic jumps pretty hard (from 907 up to 1349). Exponential smoothing is going to adapt\n";
    cout << "to that sudden growth a lot faster than a 3-month average would.\n";

    return 0;
}