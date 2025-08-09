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

    int n, tq;
    cin >> n >> tq;
    vector<Process> process(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> process[i].name >> process[i].bt;
        process[i].rem = process[i].bt;
    }

    int current_time = 0, completed = 0, last_idx = -1;
    queue<int> q;
    vector<bool> in_queue(n, false);
    vector<string> gantt_names;
    vector<int> gantt_times;

    while (completed < n)
    {
        vector<int> arrived;
        for (int i = 0; i < n; ++i)
        {
            if (!in_queue[i] && process[i].at <= current_time && i != last_idx && process[i].rem > 0)
            {
                arrived.push_back(i);
                in_queue[i] = true;
            }
        }
        sort(arrived.begin(), arrived.end(), [&](int a, int b) { return process[a].at < process[b].at; });
        for (int i : arrived)
            q.push(i);
        if (last_idx != -1 && process[last_idx].rem > 0)
            q.push(last_idx);

        if (q.empty())
        {
            if (gantt_names.empty() || gantt_names.back() != "IDLE")
            {
                gantt_names.push_back("IDLE");
                gantt_times.push_back(current_time - 1);
            }
            current_time++;
            last_idx = -1;
        }
        else
        {
            int idx = q.front();
            q.pop();

            if (gantt_names.empty() || gantt_names.back() != process[idx].name)
            {
                gantt_names.push_back(process[idx].name);
                gantt_times.push_back(current_time);
            }
            
            int exec_time = min(tq, process[idx].rem);
            current_time += exec_time;
            process[idx].rem -= exec_time;
            last_idx = idx;

            if (process[idx].rem == 0)
            {
                process[idx].ct = current_time;
                completed++;
                last_idx = -1;
            }
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