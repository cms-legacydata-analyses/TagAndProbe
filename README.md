# TagAndProbe package using Legacy Open Data samples

**Introduction**

This is a simple example of the **TagAndProbe** method using datasets of CMS Open Data. The main goal of this project is to make a simple example code applying the Tag and Probe methods, since the official TagAndProbe tool is complex. In this project, we did a more easy-to-understand code for CMS Open Data users. More about it can be seen in this twiki:

https://twiki.cern.ch/twiki/bin/view/Sandbox/TestTopic11111203


**About the Structure**

To access the data you must use the CMSSW, the structure that have the analysis environment. To do so, you have two ways:

 - **Using Vitual Machine**: You have to download the [VM Virtual Box](https://www.virtualbox.org/wiki/Download_Old_Builds). Make sure that the version you downloaded is working with your CMS VM Image. You can read more [here](http://opendata-dev.web.cern.ch/docs/cms-virtual-machine-2011). You must use the CMS SHELL in the CMS Open Data VM 1.5.1 version as you can see [here](http://opendata-dev.web.cern.ch/docs/cms-getting-started-2011). With other versions (CMS-OpenData-1.2.0" or "CMS-OpenData-1.3.0) you can use the normal terminal.


- **Using Docker Container**: If you are having problem with virtual machine you can use the [Docker Container](https://www.docker.com/resources/what-container). The instruction of installation are in this [page](https://docs.docker.com/install/). As you can see in the page, you can fetch a CMSSW image, and create and start a container using the docker run command `$ docker run --name opendata -it clelange/cmssw:5_3_32 /bin/bash`, but with that you will not be able to use ROOT. To do so, you must use the command:

`$ sudo docker run --name opendata -it -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix clelange/cmssw:5_3_32 /bin/bash`

and you will able to use ROOT. To list the containers you created use the command:

`$ sudo docker container ls -a`

To open a container, just use the command with the ID of the container that you can see the list of the containers you created.

`$ sudo docker start <ID_Container>`

`$ sudo docker attach <ID_Container>`

Now, lets create the CMSSW structure. In this example we are using the **CMSSW_5_3_32**. After you emulate you CMS Open Data ova with success, you must created a CMSSW environment and change to the `CMSSW_5_3_32/src/` directory (Notice that you use the container you do not need to use the the commands below): 

`$ cmsrel CMSSW_5_3_32`

`$ cd CMSSW_5_3_32/src/`

Launch the CMS analysis environment.

`$ cmsenv`

Create a working directory for the analyzer and go to that directory 

`$ mkdir TagAndProbeSample`

At this point, you must copy this Git to your area using the command:

`$ git clone git@github.com:sandrofonseca/TagAndProbe.git`

Go to this directory that you copied from Git and compile the code:

`$ cd TagAndProbe`

`$ scram b`

After that go to `test` folder and run the python file:

`$ cmsRun TagAndProbe_Model_Trigger.py`

Wait and you will see a root file, named TagAndProbe2019.root, that will be created. You can open this file and see its contents:

`$ root -l TagAndProbe2019.root`

`$ new TBrownser`

We use the **J/$\psi$** resonance in this example and make an output tree (root file) with the same content as the CMSSW **TagAndProbe** method. If you want study another resonance, just open the config file (TagAndProbe_Model_Trigger.py) and modify the range of mass in the line 43 and 44:

	minResonanceMass = cms.double(2.8),# in GeV
	maxResonanceMass = cms.double(3.4)# in GeV

You can change the dataset files in the 14:

	'root://eospublic.cern.ch//eos/opendata/cms/Run2011A/MuOnia/AOD/12Oct2013-v1/20000/0045B338-934C-E311-BEF1-0026189438B0.root'     
	
and the triggers in the line 36:

	PathName = cms.untracked.vstring(["HLT_Dimuon10_Jpsi_Barrel_v","HLT_Dimuon7_PsiPrime_v"]), 

	

**Recipe to produce ntuples using condor**

[Recipe Tutorial](https://twiki.cern.ch/twiki/pub/CMS/UERJLIPInternshipProgram2020/Condor_tagprobeRecipe.pdf)



	


