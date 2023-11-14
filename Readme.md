# Snowman project @ UiT

## About
The Snowman project is an IoT project where we have installed an RGB LED strip inside a "cloth" snowman. This LED strip is changing colors by listening to an MQTT server. The project was initiated as a fun Christmas decoration project by the IT department at UiT.

## MQTT server
The MQTT server is setup using Azure Container Instances. To prepare the resources you need an Azure Subscription and Contributor rights to create resources.

Example of how to create resources by using AZ CLI commands
<https://learn.microsoft.com/nb-no/azure/container-instances/>

Get storage key from storage account:

    $StorageKey=$(az storage account keys list --resource-group $myResourceGroup --account-name $StorageAccountName --query "[0].value" --output tsv)

Create Container Instance:

    az container create --resource-group $myResourceGroup --name mqttserver --image eclipse-mosquitto --dns-name-label $myDnsLabel --ports 1883 --azure-file-volume-account-name $StorageAccountName --azure-file-volume-account-key $StorageKey --azure-file-volume-share-name $ShareName --azure-file-volume-mount-path /mosquitto/config/

## Arduino
Diagram of the wiring schematic for the Arduino setup;


The Arduino board used in the project is: <https://arduino-esp8266.readthedocs.io/>

PubSub client library used for subscribing to MQTT message queue is <https://github.com/knolleary/pubsubclient>
