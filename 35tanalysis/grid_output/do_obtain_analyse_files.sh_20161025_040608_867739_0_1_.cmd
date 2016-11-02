universe          = vanilla
executable        = /fife/local/scratch/uploads/dune/wallbank/2016-10-25_040607.686516_4493/do_obtain_analyse_files.sh_20161025_040608_867739_0_1_wrap.sh
arguments         = 
output                = /fife/local/scratch/uploads/dune/wallbank/2016-10-25_040607.686516_4493/do_obtain_analyse_files.sh_20161025_040608_867739_0_1_cluster.$(Cluster).$(Process).out
error                 = /fife/local/scratch/uploads/dune/wallbank/2016-10-25_040607.686516_4493/do_obtain_analyse_files.sh_20161025_040608_867739_0_1_cluster.$(Cluster).$(Process).err
log                   = /fife/local/scratch/uploads/dune/wallbank/2016-10-25_040607.686516_4493/do_obtain_analyse_files.sh_20161025_040608_867739_0_1_.log
environment   = CLUSTER=$(Cluster);PROCESS=$(Process);CONDOR_TMP=/fife/local/scratch/uploads/dune/wallbank/2016-10-25_040607.686516_4493;CONDOR_EXEC=/tmp;DAGMANJOBID=$(DAGManJobId);MRB_INSTALL=/dune/app/users/wallbank/larsoft-base/prof/localProducts_larsoft_v06_12_00_e10_prof;MRB_DIR=/grid/fermiapp/products/larsoft/mrb/v1_08_03;RUNFILE=ew_filter_runs.txt;FILTER=1;OUTPUTDIRTAG=EW_300;OUTDIR=/pnfs/dune/persistent/users/wallbank/Sliced_And_Filtered/EW_300;GRID_USER=wallbank;IFDH_BASE_URI=http://samweb.fnal.gov:8480/sam/dune/api;JOBSUBJOBID=$(CLUSTER).$(PROCESS)@fifebatch2.fnal.gov;EXPERIMENT=dune
rank                  = Mips / 2 + Memory
job_lease_duration = 3600
notification  = Error
when_to_transfer_output = ON_EXIT_OR_EVICT
transfer_output                 = True
transfer_output_files = .empty_file
transfer_error                  = True
transfer_executable         = True
transfer_input_files = /fife/local/scratch/uploads/dune/wallbank/2016-10-25_040607.686516_4493/do_obtain_analyse_files.sh
+JobsubClientDN="/DC=org/DC=cilogon/C=US/O=Fermi National Accelerator Laboratory/OU=People/CN=Michael Wallbank/CN=UID:wallbank"
+JobsubClientIpAddress="131.225.67.240"
+Owner="wallbank"
+JobsubServerVersion="1.2.2.1"
+JobsubClientVersion="1.2.2"
+JobsubClientKerberosPrincipal="wallbank@FNAL.GOV"
+JOB_EXPECTED_MAX_LIFETIME = 28800
notify_user = wallbank@fnal.gov
x509userproxy = /var/lib/jobsub/creds/proxies/dune/x509cc_wallbank_Analysis
+RunOnGrid                          = True
+AccountingGroup = "group_dune.wallbank"
+Jobsub_Group="dune"
+JobsubJobId="$(CLUSTER).$(PROCESS)@fifebatch2.fnal.gov"
+Drain = False
+GeneratedBy ="NO_UPS_VERSION fifebatch2.fnal.gov"
+DESIRED_usage_model = "OPPORTUNISTIC"
requirements  = ((Arch=="X86_64") || (Arch=="INTEL"))&& (target.IS_Glidein==true)  && ( DesiredOS =?= NULL || stringlistimember(Target.IFOS_installed,DesiredOS)) && (stringListsIntersect(toUpper(target.HAS_usage_model), toUpper(my.DESIRED_usage_model)))


queue 1