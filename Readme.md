# Snowman project @ UiT VITE-FOF

## About
The Snowman project is an IoT project where we have installed an RGB LED strip inside a "cloth" snowman. This LED strip is changing colors by listening to an MQTT server. The project was initiated as a fun Christmas decoration project by the IT department at UiT.

## MQTT server
The MQTT server is setup using Azure Container Instances. To prepare the resource you need an Azure Subscription and Contributor rights to create resources.

Create resource by using AZ CLI commands
<https://learn.microsoft.com/nb-no/azure/container-instances/>

Get storage key from storage account:

    $StorageKey=$(az storage account keys list --resource-group $myResourceGroup --account-name $StorageAccountName --query "[0].value" --output tsv)

Create Container Instance:

    az container create --resource-group $myResourceGroup --name mqttserver --image eclipse-mosquitto --dns-name-label $myDnsLabel --ports 1883 --azure-file-volume-account-name $StorageAccountName --azure-file-volume-account-key $StorageKey --azure-file-volume-share-name $ShareName --azure-file-volume-mount-path /mosquitto/config/

## Arduino
Board: <https://arduino-esp8266.readthedocs.io/>

PubSub client library: <https://github.com/knolleary/pubsubclient>
