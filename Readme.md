# IoT Snowman

![alt text](doc/snowman.png)

*My colors are changing according to your choice. I’m listening to a MQTT topic and understand the colors listed below. Please create some scripts that get my colors to change, maybe by the weather conditions, number of users currently using a service, number of reindeers on North Pole, etc.
Eg. Paho MQTT Client library for Python can be used (<https://pypi.org/project/paho-mqtt/>).*

*NB. I’m a quite slow reader so I only reads every 5th second.*

**List of available colors:**

![alt text](doc/colors.png)

## About

The Snowman project is an IoT project where we have installed an RGB LED strip inside a "cloth" snowman. This LED strip is changing colors by listening to an MQTT server. The project was initiated as a fun Christmas decoration project by the IT department at UiT (<https://uit.no>).

## MQTT server

The MQTT server is setup using Azure Container Instances an docker image from eclipse-mosquitto - <https://hub.docker.com/_/eclipse-mosquitto>. To prepare the resources you need an Azure Subscription and Contributor rights to create resources.

Example of how to create resources by using AZ CLI commands
<https://learn.microsoft.com/nb-no/azure/container-instances/>

First we need a resource group where we can create the resources:

    az group create --name $myResourceGroup --location $location

For easier management we mount a fileshare with the config files (/mosquitto/config). For this we need a Storage Account. To create the Storage Account run:

    az storage account create --name $StorageAccountName --resource-group $myResourceGroup

Create the file share:

    az storage share create --name $ShareName --account-name $StorageAccountName

Get storage key from storage account:

    $StorageKey=$(az storage account keys list --resource-group $myResourceGroup --account-name $StorageAccountName --query "[0].value" --output tsv)

Create Container Instance:

    az container create --resource-group $myResourceGroup --name snowman-mqtt --assign-identity --image eclipse-mosquitto --dns-name-label $myDnsLabel --ports 1883 --azure-file-volume-account-name $StorageAccountName --azure-file-volume-account-key $StorageKey --azure-file-volume-share-name $ShareName --azure-file-volume-mount-path /mosquitto/

## Arduino

Diagram of the wiring schematic for the Arduino setup;

The Arduino board used in the project is: <https://arduino-esp8266.readthedocs.io/>

PubSub client library used for subscribing to MQTT message queue is <https://github.com/knolleary/pubsubclient>
