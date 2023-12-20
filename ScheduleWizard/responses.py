from datetime import datetime
from apscheduler.schedulers.background import BackgroundScheduler

# Scheduler and list to store scheduled events
scheduler = BackgroundScheduler()
scheduler.start()
scheduled_events = []

def handle_response(message) -> str:
    p_message = message.lower()

    if p_message== "hello":
        return 'Hey there!'

    # Check if the message is a scheduling request
    elif 'am' in p_message or 'pm' in p_message:
        time_part, event_part = p_message.split("'", 1)
        event_part = event_part.strip().strip("'")
        schedule_event(time_part.strip(), event_part)
        return f"Scheduled '{event_part}' at {time_part}."

    # Check if the user wants to see the schedule
    elif p_message == "show schedule":
        return show_schedule()


def schedule_event(time_str, event):
    # Convert time string to a datetime object
    schedule_time = datetime.strptime(time_str, '%I:%M %p')

    # Schedule the event and add to the list
    scheduled_events.append((schedule_time, event))
    scheduler.add_job(lambda: print(f"Reminder: {event}"), trigger='date', run_date=schedule_time)

def show_schedule():
    if not scheduled_events:
        return "No events scheduled."

    schedule_str = "Scheduled Events:\n"
    for time, event in scheduled_events:
        schedule_str += f"{time.strftime('%I:%M %p')} - {event}\n"

    return schedule_str