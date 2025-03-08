import os
from telegram import InlineKeyboardButton, InlineKeyboardMarkup, Update
from telegram.ext import Application, CommandHandler, CallbackQueryHandler, CallbackContext

# Папка, де зберігаються фото
image_folder = 'image'

# Перевірка, чи існує папка, і створення її, якщо немає
if not os.path.exists(image_folder):
    os.makedirs(image_folder)
    print(f"Папка {image_folder} була створена.")
else:
    print(f"Папка {image_folder} вже існує.")

# Отримуємо список всіх файлів у папці
photos = [os.path.join(image_folder, f) for f in os.listdir(image_folder) if os.path.isfile(os.path.join(image_folder, f))]

if len(photos) == 0:
    print("В папці немає фото!")
else:
    print(f"Знайдено {len(photos)} фото в папці.")

# Змінна для зберігання стану бота (який користувач бачить фото)
user_state = {}

# Функція привітання
async def start(update: Update, context: CallbackContext):
    keyboard = [
        [InlineKeyboardButton("Давай!", callback_data='send_photo')],
        [InlineKeyboardButton("Не хочу!", callback_data='restart')]  # Кнопка для рестарту
    ]
    reply_markup = InlineKeyboardMarkup(keyboard)
    await update.message.reply_text('Привіт! Хочеш побачити виставку фото Дмитра Сікетіна? Тоді, натискай кнопку нижче', reply_markup=reply_markup)

# Функція для надсилання фото
async def send_photo(update: Update, context: CallbackContext):
    query = update.callback_query
    user_id = query.message.chat.id

    if user_id not in user_state:
        user_state[user_id] = 0  # Ініціалізація індексу фото для користувача

    if user_state[user_id] < len(photos):
        photo_path = photos[user_state[user_id]]
        user_state[user_id] += 1  # Збільшуємо індекс для наступного фото

        print(f"Відправляється фото: {photo_path}")  # Логування

        keyboard = [
            [InlineKeyboardButton("Наступне фото", callback_data='send_photo')],
            [InlineKeyboardButton("Рестарт", callback_data='restart')]  # Кнопка для рестарту
        ]

        if user_state[user_id] >= len(photos):
            keyboard = [
                [InlineKeyboardButton("Фото закінчились", callback_data='end')],
                [InlineKeyboardButton("Рестарт", callback_data='restart')]
            ]

        reply_markup = InlineKeyboardMarkup(keyboard)

        with open(photo_path, 'rb') as photo:
            await query.message.reply_photo(photo=photo, reply_markup=reply_markup)
    else:
        await query.message.reply_text("Фото закінчились! Дякую за перегляд життєписа Дмитра Сікетіна.")

# Функція для обробки натискання кнопок
async def button(update: Update, context: CallbackContext):
    query = update.callback_query
    await query.answer()

    if query.data == 'send_photo':
        await send_photo(update, context)
    elif query.data == 'restart':
        user_id = query.message.chat.id
        user_state[user_id] = 0  # Скидаємо стан користувача

        try:
            await query.message.delete()
        except Exception as e:
            print(f"Помилка видалення повідомлення: {e}")  # Якщо повідомлення не можна видалити

        keyboard = [
            [InlineKeyboardButton("Давай!", callback_data='send_photo')],
            [InlineKeyboardButton("Не хочу!", callback_data='restart')]
        ]
        reply_markup = InlineKeyboardMarkup(keyboard)
        await query.message.reply_text('Привіт! Хочеш побачити виставку фото Дмитра Сікетіна? Тоді, натискай кнопку нижче', reply_markup=reply_markup)
    elif query.data == 'end':
        try:
            await query.edit_message_text(text="Фото закінчились! Дякую за перегляд життєписа Дмитра Сікетіна.")
        except Exception as e:
            print(f"Помилка під час редагування повідомлення: {e}")

# Основна функція
def main():
    application = Application.builder().token('7255539759:AAE4X9WiB2V9YhDaU1Fla1ofnYUKoq_niRU').build()

    application.add_handler(CommandHandler('start', start))
    application.add_handler(CallbackQueryHandler(button))

    application.run_polling()

if __name__ == '__main__':
    main()