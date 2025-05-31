Get-WmiObject -Namespace "root\LibreHardwareMonitor" -Class "Sensor" | 
Where-Object { $_.SensorType -eq "Temperature" -and $_.Name -like "*CPU*" } | 
Select-Object Value -Last 3 | ForEach-Object {
    "$($_.Value)"
}
