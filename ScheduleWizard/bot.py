import discord
import responses

async def send_message(message, user_message, is_private):
    try:
        response = responses.handle_response(user_message)
        if is_private:
            await message.author.send(response)
        else:
            await message.channel.send(response)
    except Exception as e:
        print(e)

def run_discord_bot():
    TOKEN = 'MTE4NjQyNzUwNzU0NTc1MTY5NA.GCkqTh.OYipecCxvTBRgFin4om4GKywGeFPVQe4R89Tr8'
    client = discord.Client()

    @client.event
    async def on_ready():
        print(f'{client.user} is now running!')

    @client.event
    async def on_message(message):
        if message.author == client.user:
            return

        # Check if the message is private
        is_private = isinstance(message.channel, discord.DMChannel)

        await send_message(message, message.content, is_private)

    client.run(TOKEN)
