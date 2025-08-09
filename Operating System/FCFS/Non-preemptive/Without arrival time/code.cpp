#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string name;
    int at = 0, bt, ct, tat, wt;
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    vector<Process> process(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> process[i].name >> process[i].bt;
    }
    sort(process.begin(), process.end(), [](Process a, Process b) { return a.at < b.at; });

    int current_time = 0;
    vector<string> gantt_names;
    vector<int> gantt_times;

    for (int i = 0; i < n; ++i)
    {
        if (current_time < process[i].at)
        {
            gantt_names.push_back("IDLE");
            gantt_times.push_back(current_time);
            current_time = process[i].at;
        }
        gantt_names.push_back(process[i].name);
        gantt_times.push_back(current_time);

        process[i].ct = current_time + process[i].bt;
        current_time = process[i].ct;
    }
    gantt_times.push_back(current_time);

    int tot_tat = 0, tot_wt = 0;
    for (int i = 0; i < n; ++i)
    {
        process[i].tat = process[i].ct - process[i].at;
        process[i].wt = process[i].tat - process[i].bt;
        tot_tat += process[i].tat;
        tot_wt += process[i].wt;
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n|";
    for (const auto &name : gantt_names)
    {
        cout << "\t" << name << "\t|";
    }
    cout << "\n";
    for (auto &time : gantt_times)
    {
        cout << time << "\t\t";
    }
    cout << endl;

    // Table
    sort(process.begin(), process.end(), [](Process a, Process b) { return a.name < b.name; });
    cout << "Name\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto &p : process)
    {
        cout << p.name << '\t' << p.at << '\t' << p.bt << '\t' << p.ct << '\t' << p.tat << '\t' << p.wt << '\n';
    }

    cout << "Total turn around time: " << tot_tat << endl;
    cout << "Average turn around time: " << (double)tot_tat / n << endl;
    cout << "Total waiting time: " << tot_wt << endl;
    cout << "Average waiting time: " << (double)tot_wt / n << endl;
}