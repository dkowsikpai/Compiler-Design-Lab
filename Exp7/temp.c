#include7.
#include8.
<stdio.h>
<string.h>
9.
#define STATES 99
10.
#define SYMBOLS 20
11.
12.
int N_symbols; /* number of input symbols */
13.
int N_DFA_states; /* number of DFA states */
14.
char *DFA_finals; /* final-state string */
15.
int DFAtab[STATES][SYMBOLS];
16.
17.
char StateName[STATES][STATES+1];18.
/* state-name table */
int19.
N_optDFA_states;
/* number of optimized DFA states */
50
20.
int OptDFA[STATES][SYMBOLS];
21.
char NEW_finals[STATES+1];
22.
/*
23.
24.
Print state-transition table.
25.
State names: 'A', 'B', 'C', ...
26.
*/
27.
void print_dfa_table(
28.
int tab[][SYMBOLS], /* DFA table */
29.
int nstates, /* number of states */
30.
int nsymbols, /* number of input symbols */
31.
char *finals)
32.
{
33.
int i, j;
34.
35.
puts("\nDFA: STATE TRANSITION TABLE");
36.
37.
/* input symbols: '0', '1', ... */
38.
printf(" | ");
39.
for (i = 0; i < nsymbols; i++) printf(" %c ", '0'+i);
40.
41.
printf("\n-----+--");
42.
for (i = 0; i < nsymbols; i++) printf("-----");
43.
printf("\n");
51
44.
45.
for (i = 0; i < nstates; i++) {
46.
printf(" %c | ", 'A'+i); /* state */
47.
for (j = 0; j < nsymbols; j++)
48.
printf(" %c ", tab[i][j]);49.
printf("\n");
50.
}
/* next state */
51.
printf("Final states = %s\n", finals);
52.
}
53.
54.
/*
55.
Initialize NFA table.
56.
*/
57.
void load_DFA_table()
58.
{
59.
60.
DFAtab[0][0] = 'B'; DFAtab[0][1] = 'C';
61.
DFAtab[1][0] = 'E'; DFAtab[1][1] = 'F';
62.
DFAtab[2][0] = 'A'; DFAtab[2][1] = 'A';
63.
DFAtab[3][0] = 'F'; DFAtab[3][1] = 'E';
64.
DFAtab[4][0] = 'D'; DFAtab[4][1] = 'F';
65.
DFAtab[5][0] = 'D'; DFAtab[5][1] = 'E';
66.
67.
DFA_finals = "EF";
52
68.
N_DFA_states = 6;
69.
N_symbols = 2;
70.
}
71.
72.
/*
73.
Get next-state string for current-state string.
74.
*/
75.
void get_next_state(char *nextstates, char *cur_states,
76.
int dfa[STATES][SYMBOLS], int symbol)
77.
{
78.
int i, ch;
79.
80.
for (i = 0; i < strlen(cur_states); i++)
81.
*nextstates++ = dfa[cur_states[i]-'A'][symbol];
82.
*nextstates = '\0';
83.
}
84.
85.
/*
86.
Get index of the equivalence states for state 'ch'.
87.
Equiv. class id's are '0', '1', '2', ...
88.
*/
89.
char equiv_class_ndx(char ch, char stnt[][STATES+1], int n)
90.
{
91.
int i;
53
92.
93.
for (i = 0; i < n; i++)
94.
if (strchr(stnt[i], ch)) return i+'0';
95.
return -1; /* next state is NOT defined */
}
96.
97.
/*
98.
99.
Check if all the next states belongs to same equivalence class.
100.
Return value:
101.
If next state is NOT unique, return 0.
102.
If next state is unique, return next state --> 'A/B/C/...'
103.
's' is a '0/1' string: state-id's
104.
*/
105.
char is_one_nextstate(char *s)
106.
{
107.
char equiv_class; /* first equiv. class */
108.
109.
while (*s == '@') s++;
110.
equiv_class = *s++; /* index of equiv. class */
111.
112.
while (*s) {
113.
if (*s != '@' && *s != equiv_class) return 0;
114.
s++;
115.
}
54
116.
117.
return equiv_class; /* next state: char type */
118.
}
119.
120.
int state_index(char *state, char stnt[][STATES+1], int n, int *pn,
121.
int cur) /* 'cur' is added only for 'printf()' */
122.
{
123.
int i;
124.
char state_flags[STATES+1]; /* next state info. */
125.
126.
if (!*state) return -1; /* no next state */
127.
128.
for (i = 0; i < strlen(state); i++)
129.
state_flags[i] = equiv_class_ndx(state[i], stnt, n);
130.
state_flags[i] = '\0';
131.
132.
printf(" %d:[%s]\t--> [%s] (%s)\n",
133.
cur, stnt[cur], state, state_flags);
134.
135.
if (i=is_one_nextstate(state_flags))
136.
return i-'0'; /* deterministic next states */
137.
else {
138.
strcpy(stnt[*pn], state_flags); /* state-division info */
139.
return (*pn)++;
55
}
140.
}
141.
142.
/*
143.
144.
Divide DFA states into finals and non-finals.
145.
*/
146.
int init_equiv_class(char statename[][STATES+1], int n, char *finals)
147.
{
148.
int i, j;
149.
150.
if (strlen(finals) == n) { /* all states are final states */
151.
strcpy(statename[0], finals);
152.
return 1;
153.
}
154.
155.
strcpy(statename[1],156.
finals);/* final state group */
157.
for (i=j=0; i < n; i++) {
158.
if (i == *finals-'A') {
159.
finals++;
160.
} else statename[0][j++] = i+'A';
161.
}
162.
statename[0][j] = '\0';
163.
56
}
164.
return165.
2;
166.
/*
167.
168.
Get optimized DFA 'newdfa' for equiv. class 'stnt'.
169.
*/
170.
int get_optimized_DFA(char stnt[][STATES+1], int n,
171.
int dfa[][SYMBOLS], int n_sym, int newdfa[][SYMBOLS])
172.
{
173.
int n2=n;
 /* 'n' + <num. of state-division info> */
174.
int i, j;
175.
char nextstate[STATES+1];
176.
177.
for (i = 0; i < n; i++) { /* for each pseudo-DFA state */
178.
for (j = 0; j < n_sym; j++) { /* for each input symbol */
179.
get_next_state(nextstate, stnt[i], dfa, j);
180.
newdfa[i][j] = state_index(nextstate, stnt, n, &n2, i)+'A';
181.
}
182.
}
183.
}
184.
return185.
n2;
186.
/*
187.
57
188.
char 'ch' is appended at the end of 's'.
189.
*/
190.
void chr_append(char *s, char ch)
191.
{
192.
int n=strlen(s);
193.
194.
*(s+n) = ch;
195.
*(s+n+1) = '\0';
196.
}
197.
198.
void sort(char stnt[][STATES+1], int n)
199.
{
200.
int i, j;
201.
char temp[STATES+1];
202.
203.
for (i = 0; i < n-1; i++)
204.
for (j = i+1; j < n; j++)
205.
if (stnt[i][0] > stnt[j][0]) {
206.
strcpy(temp, stnt[i]);
207.
strcpy(stnt[i], stnt[j]);
208.
strcpy(stnt[j], temp);
209.
}
210.
}
211.
58
212.
/*
213.
Divide first equivalent class into subclasses.
214.
stnt[i1] : equiv. class to be segmented
215.
stnt[i2] : equiv. vector for next state of stnt[i1]
216.
Algorithm:
217.
- stnt[i1] is splitted into 2 or more classes 's1/s2/...'
218.
- old equiv. classes are NOT changed, except stnt[i1]
219.
- stnt[i1]=s1, stnt[n]=s2, stnt[n+1]=s3, ...
220.
Return value: number of NEW equiv. classses in 'stnt'.
221.
*/
222.
int split_equiv_class(char stnt[][STATES+1],
223.
int i1, /* index of 'i1'-th equiv. class */
224.
int i2, /* index of equiv. vector for 'i1'-th class */
225.
int n, /* number of entries in 'stnt' */
226.
int n_dfa) /* number of source DFA entries */
227.
{
228.
char *old=stnt[i1], *vec=stnt[i2];
229.
int i, n2, flag=0;
230.
char newstates[STATES][STATES+1]; /* max. 'n' subclasses */
231.
232.
for (i=0; i < STATES; i++) newstates[i][0] = '\0';
233.
234.
for (i=0; vec[i]; i++)
235.
chr_append(newstates[vec[i]-'0'], old[i]);
59
236.
237.
for (i=0, n2=n; i < n_dfa; i++) {
238.
if (newstates[i][0]) {
239.
if (!flag) { /* stnt[i1] = s1 */
240.
strcpy(stnt[i1], newstates[i]);
241.
flag = 1; /* overwrite parent class */
242.
} else /* newstate is appended in 'stnt' */
243.
244.
}
245.
}
246.
strcpy(stnt[n2++], newstates[i]);
247.
sort(stnt, n2); /* sort equiv. classes */
248.
249.
return n2; /* number of NEW states(equiv. classes) */
250.
}
251.
252.
/*
253.
Equiv. classes are segmented and get NEW equiv. classes.
254.
*/
255.
int set_new_equiv_class(char stnt[][STATES+1], int n,
256.
int newdfa[][SYMBOLS], int n_sym, int n_dfa)
257.
{
258.
int i, j, k;
259.
60
260.
for (i = 0; i < n; i++) {
261.
for (j = 0; j < n_sym; j++) {
262.
k = newdfa[i][j]-'A'; /* index of equiv. vector */
263.
if (k >= n) /* equiv. class 'i' should be segmented */
264.
265.
}
266.
}
267.
return split_equiv_class(stnt, i, k, n, n_dfa);
}
268.
return269.
n;
270.
271.
void print_equiv_classes(char stnt[][STATES+1], int n)
272.
{
273.
int i;
274.
275.
printf("\nEQUIV. CLASS CANDIDATE ==>");
276.
for (i = 0; i < n; i++)
277.
printf(" %d:[%s]", i, stnt[i]);
278.
printf("\n");
279.
}
280.
281.
/*
282.
State-minimization of DFA: 'dfa' --> 'newdfa'
283.
Return value: number of DFA states.
61
284.
*/
285.
int optimize_DFA(
286.
int dfa[][SYMBOLS], /* DFA state-transition table */
287.
int n_dfa, /* number of DFA states */
288.
int n_sym, /* number of input symbols */
289.
char *finals, /* final states of DFA */
290.
char stnt[][STATES+1], /* state name table */
291.
int newdfa[][SYMBOLS]) /* reduced DFA table */
292.
{
293.
char nextstate[STATES+1];
294.
int n; /* number of new DFA states */
295.
int n2; /* 'n' + <num. of state-dividing info> */
296.
297.
n = init_equiv_class(stnt, n_dfa, finals);
298.
299.
while (1) {
300.
print_equiv_classes(stnt, n);
301.
n2 = get_optimized_DFA(stnt, n, dfa, n_sym, newdfa);
302.
if (n != n2)
303.
n = set_new_equiv_class(stnt, n, newdfa, n_sym, n_dfa);
304.
else break; /* equiv. class segmentation ended!!! */
305.
}
306.
307.
returnn;/* number of DFA states */
62
}
308.
309.
310.
/*
311.
Check if 't' is a subset of 's'.
312.
*/
313.
int is_subset(char *s, char *t)
314.
{
315.
int i;
316.
317.
for (i = 0; *t; i++)
318.
if (!strchr(s, *t++)) return 0;
319.
return 1;
320.
}
321.
322.
/*
323.
New finals states of reduced DFA.
324.
*/
325.
void get_NEW_finals(
326.
char *newfinals, /* new DFA finals */
327.
char *oldfinals, /* source DFA finals */
328.
char stnt[][STATES+1], /* state name table */
329.
int n) /* number of states in 'stnt' */
330.
{
331.
int i;
63
332.
333.
for (i = 0; i < n; i++)
334.
if (is_subset(oldfinals, stnt[i])) *newfinals++ = i+'A';
335.
*newfinals++ = '\0';
}
336.
337.
338.
void main()
339.
{
340.
load_DFA_table();
341.
print_dfa_table(DFAtab, N_DFA_states, N_symbols, DFA_finals);
342.
343.
N_optDFA_states = optimize_DFA(DFAtab, N_DFA_states,
344.
N_symbols, DFA_finals, StateName, OptDFA);
345.
get_NEW_finals(NEW_finals, DFA_finals, StateName, N_optDFA_states);
346.
347.
print_dfa_table(OptDFA, N_optDFA_states, N_symbols, NEW_finals);
348.
}
