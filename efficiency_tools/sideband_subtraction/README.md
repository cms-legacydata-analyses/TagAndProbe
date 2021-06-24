# Tag & Probe Fitting

> Tag &amp; probe efficiency calculus project

## Necessary files and preparation

The analysed datas are from those files:
* [0] DoubleMu_data_ntuples.tar - obsolete (Old ntupple. Need to be merged. Current name after merge should be `data_histoall.root`)
* [1] [Run2011AMuOnia_mergeNtuple.root](https://drive.google.com/drive/u/0/folders/1Nu9Al7SV1F60TMFxKZVBIMvgEWAdzida)
* [2] [JPsiToMuMu_mergeMCNtuple.root](https://drive.google.com/drive/u/0/folders/1Nu9Al7SV1F60TMFxKZVBIMvgEWAdzida)

After download one of those files, you can run the code. Don't forget to use `int useFile` in `macro.cpp` file to set which ntupple will you analyse. Just set the current index in `const char *files[]`.

## Preferences and setup

Change this line to specify the ntupple you are analysing by choosing 0 (old ntupple), 1 (run 2011 ntupple) or 2 (monte carlo ntupple):

```cpp
int useFile = 1;
```

More options can be found at `config` folder

## Development setting and run

It is necessary to have [ROOT](https://root.cern.ch/root/html534/guides/users-guide/InstallandBuild.html), CERN's software, installed on your machine.

Go on your folder where the file code is downloaded and run:

```sh
$ cd main
$ root -l -n
root[1] .x macro()
```

## Output
Images are created in `../result` folder by default. User can choose where to save it in options. In addition, a .root file is generated named `generated_hist.root` with all canvas and histograms.
