#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string name;
    int at = 0, bt, ct, tat, wt, rem;
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
        process[i].rem = process[i].bt;
    }

    int completed = 0, current_time = 0, prev = -1;
    vector<bool> is_completed(n, false);
    vector<string> gantt_names;
    vector<int> gantt_times;

    while (completed < n)
    {
        int idx = -1, min_rem = INT_MAX;
        for (int i = 0; i < n; ++i)
        {
            if (process[i].at <= current_time && !is_completed[i] && process[i].rem < min_rem && process[i].rem > 0)
            {
                min_rem = process[i].rem;
                idx = i;
            }
        }
        if (idx != -1)
        {
            if (gantt_names.empty() || gantt_names.back() != process[idx].name)
            {
                gantt_names.push_back(process[idx].name);
                gantt_times.push_back(current_time);
            }
            
            process[idx].rem--;
            current_time++;
            if (process[idx].rem == 0)
            {
                process[idx].ct = current_time;
                is_completed[idx] = true;
                completed++;
            }
        }
        else
        {
            if (gantt_names.empty() || gantt_names.back() != "IDLE")
            {
                gantt_names.push_back("IDLE");
                gantt_times.push_back(current_time);
            }
            current_time++;
        }
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

    cout << "\nGantt Chart:\n|";
    for (const auto &name : gantt_names)
    {
        cout << "\t" << name << "\t|";
    }
    cout << "\n";
    for(auto &time : gantt_times)
    {
        cout << time << "\t\t";
    }
    cout << endl;

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